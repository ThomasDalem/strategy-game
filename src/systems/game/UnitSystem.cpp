#include "UnitSystem.hpp"
#include "components/Sprite.hpp"
#include "components/game/Unit.hpp"
#include "components/game/Enemy.hpp"
#include "components/game/Allied.hpp"
#include "components/Circle.hpp"
#include "entities/Units.hpp"
#include "utils/TransformUtils.hpp"

void shootEnemies(entt::registry &reg, uint64_t gameTime)
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
            const uint64_t lastShot = gameTime - infos.lastShotTime;

            if (lastShot > 1000.0 / infos.firerate && getDistance(unitSprite.pos, enemySprite.pos) < infos.range) {
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

    const auto units = reg.view<Unit, Allied, Circle>();

    for (entt::entity unit : units) {
        Allied &allied = reg.get<Allied>(unit);
        Circle &circle = reg.get<Circle>(unit);

        if (allied.isDragged) {
            allied.isDragged = false;
            circle.hidden = true;
        }
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
