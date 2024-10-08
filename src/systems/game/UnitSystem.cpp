#include "UnitSystem.hpp"

#include <limits>
#include <iostream>
#include <random>
#include <cmath>
#include <array>

#include "utils/TransformUtils.hpp"
#include "utils/SoundLoader.hpp"
#include "utils/Random.hpp"
#include "utils/WinInfo.hpp"

#include "components/Sprite.hpp"
#include "components/Circle.hpp"
#include "components/Movement.hpp"
#include "components/game/Enemy.hpp"
#include "components/game/Allied.hpp"
#include "components/game/Selected.hpp"
#include "components/game/Waypoint.hpp"
#include "components/tags/Base.hpp"
#include "components/Sound.hpp"

#include "entities/Units.hpp"
#include "entities/Bullet.hpp"

#include "game/Data.hpp"

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
        if (infos.type == UnitType::ARMORED)
        {
            makeBullet(reg, unitPos, enemyPos, bulletSpeed, "far_explosion");
        }
        else
        {
            makeBullet(reg, unitPos, enemyPos, bulletSpeed);
        }

        // SFX
        std::string group = getUnitSoundGroup(infos) + "/shooting";
        SDL::MixChunk *chunk = SoundLoader::getInstance().loadRandomChunk(group);

        reg.emplace_or_replace<Sound>(unit, chunk);
        if (chunk)
        {
            chunk->play();
        }

        enemyInfos.health -= infos.damage;
        infos.lastShotTime = gameTime;
    }
}

void engage(entt::registry &reg, float gameTime, auto &units, auto &enemies)
{
    for (const entt::entity unit : units) {
        Unit &infos = reg.get<Unit>(unit);

        infos.target = findTarget(reg, unit, enemies);
        engageTarget(reg, gameTime, unit, infos.target);
    }
}

void makeEngagements(entt::registry &reg, float gameTime)
{
    {
        const auto unitsView = reg.view<Unit>(entt::exclude<Enemy>);
        const auto enemiesView = reg.view<Unit, Enemy>();
        engage(reg, gameTime, unitsView, enemiesView);
    }
    const auto unitsView = reg.view<Unit>(entt::exclude<Allied>);
    const auto enemiesView = reg.view<Unit, Allied>();
    engage(reg, gameTime, unitsView, enemiesView);
}

void dragUnits(entt::registry &reg)
{
    const auto units = reg.view<Sprite, Unit, Allied>();
    int x = 0;
    int y = 0;

    SDL_GetMouseState(&x, &y);

    const Vec2f pos(static_cast<float>(x), static_cast<float>(y));

    for (entt::entity unit : units) {
        const Allied &allied = reg.get<Allied>(unit);

        if (allied.isDragged) {
            setPosition(reg, unit, pos);
        }
    }
}

void createUnit(entt::registry &reg, TexturesLoader &textureLoader, UnitType unitType)
{
    const auto baseView = reg.view<Base>();

    if (baseView.empty())
    {
        return;
    }
    if (Data::getInstance().supplies < unitPrices[unitType])
    {
        return;
    }

    const Position &basePos = reg.get<Position>(baseView.begin()[0]);

    entt::entity unit = entt::null;

    switch (unitType)
    {
    case UnitType::INFANTRY:
        unit = makeAlliedInfantry(reg, textureLoader, basePos.x, basePos.y);
        break;
    case UnitType::ARMORED:
        unit = makeFriendlyArmored(reg, textureLoader, basePos.x, basePos.y);
        break;
    default:
        break;
    }

    if (unit == entt::null)
    {
        return;
    }

    RandomFloat ran(-1.f, 1.f);
    const float angle = ran.generate() * M_PI * 2;
    const float radius = 100.f;
    Vec2f dir(std::cos(angle) * radius, std::sin(angle) * radius);

    dir += basePos;

    reg.emplace<Waypoint>(unit, dir);

    Data::getInstance().supplies -= unitPrices[unitType];
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
            static_cast<int>(sprite.rect.width * (static_cast<float>(unit.health) / unit.totalHealth)),
            10
        };

        const uint8_t green = 255 * (static_cast<float>(unit.health) / unit.totalHealth);
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
    const auto view = reg.view<Unit, Allied, Sprite, Circle>();
    const Vec2i mousePos = WinInfo::getInstance().getScaledMousePos();

    unselectUnits(reg);
    for (const entt::entity unit : view) {
        const Sprite &unitSprite = reg.get<Sprite>(unit);
        if (pointInRect(unitSprite.rect, mousePos.x, mousePos.y)) {
            Circle &unitCircle = reg.get<Circle>(unit);
            reg.emplace<Selected>(unit);
            unitCircle.hidden = false;
            SDL::MixChunk *chunk = SoundLoader::getInstance().loadChunk("select");
            if (chunk)
            {
                chunk->play();
            }
            return;
        }
    }
}

void setUnitWaypoint(entt::registry &reg)
{
    const auto view = reg.view<Unit, Allied, Selected>();
    const Vec2i mousePos = WinInfo::getInstance().getScaledMousePos();
 
    for (const entt::entity e : view) {
        reg.emplace_or_replace<Waypoint>(e, Vec2f{static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)});

        const Unit &unit = reg.get<Unit>(e);
        std::string group = getUnitSoundGroup(unit) + "/roger";
        SDL::MixChunk *chunk = SoundLoader::getInstance().loadRandomChunk(group);

        reg.emplace_or_replace<Sound>(e, chunk);
        if (chunk == nullptr)
        {
            continue;
        }
        chunk->play();
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

void handleInputs(entt::registry &reg, SDL_Event &e)
{
    if (e.type == SDL_MOUSEBUTTONDOWN) {
        if (e.button.button == SDL_BUTTON_LEFT) {
            selectUnit(reg);
        }
        else if (e.button.button == SDL_BUTTON_RIGHT) {
            setUnitWaypoint(reg);
        }
    }
}

void checkUnitsHealth(entt::registry &reg)
{
    reg.view<Unit>().each([&reg](entt::entity e, Unit &unit){
        if (unit.health <= 0) {

            Enemy *enemy = reg.try_get<Enemy>(e);
            if (enemy != nullptr) {
                Data::getInstance().supplies += 10;
            }
            reg.destroy(e);
        }
    });
}

std::string getUnitSoundGroup(const Unit &unit)
{
    switch (unit.type)
    {
    case UnitType::INFANTRY:
        return "/unit_type/infantry";
    case UnitType::ARMORED:
        return "/unit_type/armored";
    default:
        break;
    }
    return "";
}

