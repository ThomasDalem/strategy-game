#include "UnitSystem.hpp"
#include "components/Sprite.hpp"
#include "components/game/UnitInfo.hpp"
#include "components/game/Enemy.hpp"

void shootEnemies(entt::registry &reg, uint64_t gameTime)
{
    const auto buildingsView = reg.view<UnitInfo>();
    const auto enemiesView = reg.view<Enemy>();

    for (entt::entity building : buildingsView) {
        const Sprite &buildingSprite = reg.get<Sprite>(building);
        UnitInfo &infos = reg.get<UnitInfo>(building);

        for (entt::entity enemy : enemiesView) {
            const Sprite &enemySprite = reg.get<Sprite>(enemy);
            Enemy &enemyInfos = reg.get<Enemy>(enemy);

            if (gameTime - infos.lastShotTime > 1000.0 / infos.firerate && getDistance(buildingSprite.pos, enemySprite.pos) < infos.range) {
                enemyInfos.health -= infos.damage;
                infos.lastShotTime = gameTime;
            }
        }
    }
}
