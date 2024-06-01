#include "EnemySystem.hpp"

#include "utils/Timer.hpp"

#include "components/Movement.hpp"
#include "components/Sprite.hpp"
#include "components/Position.hpp"
#include "components/tags/Base.hpp"
#include "components/game/Enemy.hpp"
#include "components/game/Unit.hpp"

#include "entities/Units.hpp"

#include <iostream>

void moveEnemies(entt::registry &reg)
{
    const auto baseView = reg.view<Base>();
    const auto enemyView = reg.view<Enemy>();

    if (baseView.size() == 0) {
        return;
    }

    const Position &basePos = reg.get<Position>(baseView.begin()[0]);

    for (const entt::entity enemy : enemyView) {
        const Position &enemyPos = reg.get<Position>(enemy);
        Movement &movement = reg.get<Movement>(enemy);

        movement.direction = normalize(basePos - enemyPos);

        if (getDistance(basePos, enemyPos) < 100.f) {
            movement.move = false;
        }
        else {
            movement.move = true;
        }
    }
}

void spawnEnemies(entt::registry &reg, TexturesLoader &textureLoader, float deltaTime)
{
    static const float spawnRate = 5.f; // in seconds
    static float lastSpawnTime = 0.f;

    if (deltaTime - lastSpawnTime > spawnRate) {
        makeEnemyInfantry(reg, textureLoader, 100.f, 100.f);
        lastSpawnTime = deltaTime;
    }
}

void enemySystem(entt::registry &reg)
{
    moveEnemies(reg);
}
