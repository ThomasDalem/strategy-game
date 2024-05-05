#include "UnitSystem.hpp"

#include <limits>
#include <iostream>

#include "utils/TransformUtils.hpp"

#include "components/Sprite.hpp"
#include "components/Circle.hpp"
#include "components/Movement.hpp"
#include "components/game/Unit.hpp"
#include "components/game/Enemy.hpp"
#include "components/game/Allied.hpp"
#include "components/game/Selected.hpp"
#include "components/game/Waypoint.hpp"

#include "entities/Units.hpp"
#include "entities/Bullet.hpp"

entt::entity findTarget(entt::registry &reg, entt::entity unit, auto &enemiesView)
{
    const Position &unitPos = reg.get<Position>(unit);
    Unit &infos = reg.get<Unit>(unit);

    if (reg.valid(infos.target) && getDistance(unitPos, reg.get<Position>(infos.target)) < infos.range) {
        return infos.target;
    }

    entt::entity closestEnemy = entt::null;
    float closestEnemyDistance = std::numeric_limits<float>::infinity();

    for (const entt::entity enemy : enemiesView) {
        const Position &enemyPos = reg.get<Position>(enemy);
        const float distance = getDistance(unitPos, enemyPos);

        if (distance < infos.range && distance < closestEnemyDistance) {
            closestEnemy = enemy;
            closestEnemyDistance = distance;
        }
    }

    return closestEnemy;
}

void engageTarget(entt::registry &reg, float gameTime, entt::entity unit, entt::entity enemy)
{
    Unit &infos = reg.get<Unit>(unit);

    if (infos.target == entt::null || reg.valid(infos.target) == false) {
        return;
    }

    const float lastShot = gameTime - infos.lastShotTime;
    const Position &unitPos = reg.get<Position>(unit);
    const Position &enemyPos = reg.get<Position>(enemy);
    Unit &enemyInfos = reg.get<Unit>(enemy);

    if (lastShot > infos.firerate / 10.f && getDistance(unitPos, enemyPos) < infos.range) {
        const float bulletSpeed = 600.f;
        makeBullet(reg, unitPos, enemyPos, bulletSpeed);

        enemyInfos.health -= infos.damage;
        infos.lastShotTime = gameTime;
    }
}

void makeEngagements(entt::registry &reg, float gameTime)
{
    const auto unitsView = reg.view<Unit>(entt::exclude<Enemy>);
    const auto enemiesView = reg.view<Enemy>();

    for (const entt::entity unit : unitsView) {
        Unit &infos = reg.get<Unit>(unit);

        if (infos.isActive == false) {
            continue;
        }
        infos.target = findTarget(reg, unit, enemiesView);
        engageTarget(reg, gameTime, unit, infos.target);
    }
}

void dragUnits(entt::registry &reg)
{
    const auto units = reg.view<Sprite, Unit, Allied>();
    int x = 0;
    int y = 0;

    SDL_GetMouseState(&x, &y);

    for (entt::entity unit : units) {
        const Allied &allied = reg.get<Allied>(unit);

        if (allied.isDragged) {
            setPosition(reg, unit, {static_cast<float>(x), static_cast<float>(y)});
        }
    }
}

void createUnit(entt::registry &reg, TexturesLoader &textureLoader)
{
    int x = 0;
    int y = 0;

    SDL_GetMouseState(&x, &y);
    const entt::entity unit = makeAlliedInfantry(reg, textureLoader, static_cast<float>(x), static_cast<float>(y));
    Allied &allied = reg.get<Allied>(unit);
    allied.isDragged = true;
}

void deployUnit(entt::registry &reg)
{
    int x = 0;
    int y = 0;

    SDL_GetMouseState(&x, &y);

    const auto view = reg.view<Unit, Allied, Circle>();

    for (entt::entity e : view) {
        Allied &allied = reg.get<Allied>(e);
        Circle &circle = reg.get<Circle>(e);
        Unit &unit = reg.get<Unit>(e);

        if (allied.isDragged) {
            allied.isDragged = false;
            circle.hidden = true;
            unit.isActive = true;
        }
    }
}

void drawHealth(entt::registry &reg, SDL::Renderer &renderer)
{
    const auto view = reg.view<Unit, Sprite>();

    for (const entt::entity e : view) {
        const Sprite &sprite = reg.get<Sprite>(e);
        const Unit &unit = reg.get<Unit>(e);

        const RectI rect {
            static_cast<int>(sprite.pos.x),
            static_cast<int>(sprite.pos.y + sprite.rect.height + 5),
            static_cast<int>(sprite.rect.width * (static_cast<float>(unit.health) / 100)),
            10
        };

        const uint8_t green = 255 * (static_cast<float>(unit.health) / 100);
        const uint8_t red = 255 - green;
        renderer.drawRect(rect, red, green, 0, 255);
    }
}

void unselectUnits(entt::registry &reg)
{
    const auto view = reg.view<Unit, Allied, Circle, Selected>();

    for (const entt::entity unit : view) {
        Circle &unitCircle = reg.get<Circle>(unit);

        unitCircle.hidden = true;
        reg.remove<Selected>(unit);
    }
}

void selectUnit(entt::registry &reg)
{
    int x = 0;
    int y = 0;

    SDL_GetMouseState(&x, &y);

    const auto view = reg.view<Unit, Allied, Sprite, Circle>();

    unselectUnits(reg);
    for (const entt::entity unit : view) {
        const Sprite &unitSprite = reg.get<Sprite>(unit);
        if (pointInRect(unitSprite.rect, x, y)) {
            Circle &unitCircle = reg.get<Circle>(unit);
            reg.emplace<Selected>(unit);
            unitCircle.hidden = false;
            return;
        }
    }
}

void setUnitWaypoint(entt::registry &reg)
{
    const auto view = reg.view<Unit, Allied, Selected>();
    int x = 0;
    int y = 0;

    SDL_GetMouseState(&x, &y);

    for (const entt::entity e : view) {
        reg.emplace_or_replace<Waypoint>(e, Vec2f{static_cast<float>(x), static_cast<float>(y)});
    }
}

void moveUnits(entt::registry &reg)
{
    const auto view = reg.view<Unit, Waypoint, Position>();

    for (const entt::entity e : view) {
        const Waypoint &waypoint = reg.get<Waypoint>(e);
        const Unit &unit = reg.get<Unit>(e);
        const Position &pos = reg.get<Position>(e);
        const Vec2f direction = normalize(waypoint.pos - pos);
        Movement &mov = reg.get_or_emplace<Movement>(e); 

        mov.direction = direction;
        mov.speed = unit.speed;
        mov.move = true;
    }
}

void handleInputs(entt::registry &reg, TexturesLoader &textureLoader, SDL_Event &e)
{
    if (e.type == SDL_KEYDOWN) {
        if (e.key.keysym.sym == SDLK_b) {
            createUnit(reg, textureLoader);
        }
    }
    else if (e.type == SDL_MOUSEBUTTONDOWN) {
        if (e.button.button == SDL_BUTTON_LEFT) {
            selectUnit(reg);
            deployUnit(reg);
        }
        else if (e.button.button == SDL_BUTTON_RIGHT) {
            setUnitWaypoint(reg);
        }
    }
}
