#include "EnemySystem.hpp"

#include <cmath>

#include "utils/Timer.hpp"
#include "utils/Random.hpp"

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

    if (baseView.empty()) {
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

    if (deltaTime - lastSpawnTime < spawnRate)
    {
        return;
    }

    const auto baseView = reg.view<Base>();

    if (baseView.empty())
    {
        return;
    }

    const Position &basePos = reg.get<Position>(baseView.begin()[0]);
    RandomFloat random(-1.f, 1.f);

    const float angle = random.generate() * M_PI * 2;
    const float radius = 1000.f;
    const float x = std::cos(angle) * radius + basePos.x;
    const float y = std::sin(angle) * radius + basePos.y;

    std::uniform_int_distribution<> distrib2(1, 10);

    if (distrib2(gen) == 1)
    {
        makeHostileArmored(reg, textureLoader, x, y);
    }
    else
    {
        makeEnemyInfantry(reg, textureLoader, x, y);
    }
    lastSpawnTime = deltaTime;
}

void enemySystem(entt::registry &reg)
{
    moveEnemies(reg);
}
