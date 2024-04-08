#include "UnitSystem.hpp"
#include "components/Sprite.hpp"
#include "components/game/UnitInfo.hpp"
#include "components/game/Enemy.hpp"
#include "components/game/Allied.hpp"
#include "entities/Units.hpp"
#include "utils/TransformUtils.hpp"

void shootEnemies(entt::registry &reg, uint64_t gameTime)
{
    const auto unitsView = reg.view<UnitInfo>(entt::exclude<Enemy>);
    const auto enemiesView = reg.view<Enemy>();

    for (entt::entity unit : unitsView) {
        const Sprite &unitSprite = reg.get<Sprite>(unit);
        UnitInfo &infos = reg.get<UnitInfo>(unit);

        if (infos.isActive == false) {
            continue;
        }

        for (entt::entity enemy : enemiesView) {
            const Sprite &enemySprite = reg.get<Sprite>(enemy);
            UnitInfo &enemyInfos = reg.get<UnitInfo>(enemy);
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
    const auto units = reg.view<Sprite, UnitInfo, Allied>();
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

void deployUnit(entt::registry &reg, TexturesLoader &textureLoader)
{
    int x = 0;
    int y = 0;

    SDL_GetMouseState(&x, &y);
    const entt::entity unit = makeAlliedInfantry(reg, textureLoader, static_cast<double>(x), static_cast<double>(y));
    Allied &allied = reg.get<Allied>(unit);
    allied.isDragged = true;
}

void handleInputs(entt::registry &reg, TexturesLoader &textureLoader, SDL_Event &e)
{
    if (e.key.keysym.sym == SDLK_b) {
        deployUnit(reg, textureLoader);
    }
}
