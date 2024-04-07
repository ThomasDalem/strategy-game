#include "BuildingsFiring.hpp"
#include "components/Sprite.hpp"
#include "components/game/BuildingInfo.hpp"
#include "components/game/Enemy.hpp"
#include <iostream>

void shootEnemies(entt::registry &reg, uint64_t gameTime)
{
    const auto buildingsView = reg.view<BuildingInfo>();
    const auto enemiesView = reg.view<Enemy>();

    for (entt::entity building : buildingsView) {
        const Sprite &buildingSprite = reg.get<Sprite>(building);
        BuildingInfo &infos = reg.get<BuildingInfo>(building);

        for (entt::entity enemy : enemiesView) {
            const Sprite &enemySprite = reg.get<Sprite>(enemy);
            Enemy &enemyInfos = reg.get<Enemy>(enemy);

            if (gameTime - infos.lastShotTime > 1000.0 / infos.firerate && getDistance(buildingSprite.pos, enemySprite.pos) < infos.range) {
                enemyInfos.health -= infos.damage;
                infos.lastShotTime = gameTime;
                std::cout << "shooting\n";
            }
        }
    }
}
