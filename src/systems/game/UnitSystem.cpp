#include "UnitSystem.hpp"
#include "utils/TransformUtils.hpp"
#include "components/Sprite.hpp"
#include "components/game/Unit.hpp"
#include "components/game/Enemy.hpp"
#include "components/game/Allied.hpp"
#include "components/Circle.hpp"
#include "entities/Units.hpp"
#include "entities/Bullet.hpp"

void shootEnemies(entt::registry &reg, float gameTime)
{
    const auto unitsView = reg.view<Unit>(entt::exclude<Enemy>);
    const auto enemiesView = reg.view<Enemy>();

    for (entt::entity unit : unitsView) {
        const Sprite &unitSprite = reg.get<Sprite>(unit);
        Unit &infos = reg.get<Unit>(unit);

        if (infos.isActive == false) {
            continue;
        }

        for (entt::entity enemy : enemiesView) {
            const Sprite &enemySprite = reg.get<Sprite>(enemy);
            Unit &enemyInfos = reg.get<Unit>(enemy);
            const float lastShot = gameTime - infos.lastShotTime;

            if (lastShot > infos.firerate / 10.0 && getDistance(unitSprite.pos, enemySprite.pos) < infos.range) {
                const Vec2d unitCenter = unitSprite.pos + unitSprite.texture->getCenter();
                const Vec2d enemyCenter = enemySprite.pos + enemySprite.texture->getCenter();
                makeBullet(reg, unitCenter, enemyCenter, 250);

                enemyInfos.health -= infos.damage;
                infos.lastShotTime = gameTime;
            }
        }
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
            setPosition(reg, unit, {static_cast<double>(x), static_cast<double>(y)});
        }
    }
}

void createUnit(entt::registry &reg, TexturesLoader &textureLoader)
{
    int x = 0;
    int y = 0;

    SDL_GetMouseState(&x, &y);
    const entt::entity unit = makeAlliedInfantry(reg, textureLoader, static_cast<double>(x), static_cast<double>(y));
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

    for (entt::entity e : view) {
        const Sprite &sprite = reg.get<Sprite>(e);
        const Unit &unit = reg.get<Unit>(e);

        const RectI rect {
            static_cast<int>(sprite.pos.x),
            static_cast<int>(sprite.pos.y + sprite.rect.height + 5),
            static_cast<int>(sprite.rect.width * (static_cast<double>(unit.health) / 100)),
            10
        };

        const uint8_t green = 255 * (static_cast<double>(unit.health) / 100);
        const uint8_t red = 255 - green;
        renderer.drawRect(rect, red, green, 0, 255);
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
            deployUnit(reg);
        }
    }
}
