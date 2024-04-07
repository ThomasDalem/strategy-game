#include "UnitSystem.hpp"
#include "components/Sprite.hpp"
#include "components/game/UnitInfo.hpp"
#include "components/game/Enemy.hpp"

void shootEnemies(entt::registry &reg, uint64_t gameTime)
{
    const auto unitsView = reg.view<UnitInfo>(entt::exclude<Enemy>);
    const auto enemiesView = reg.view<Enemy>();

    for (entt::entity unit : unitsView) {
        const Sprite &unitSprite = reg.get<Sprite>(unit);
        UnitInfo &infos = reg.get<UnitInfo>(unit);

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
