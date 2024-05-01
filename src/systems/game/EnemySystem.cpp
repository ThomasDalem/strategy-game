#include "EnemySystem.hpp"

#include "components/tags/Base.hpp"
#include "components/Movement.hpp"
#include "components/game/Enemy.hpp"
#include "components/Sprite.hpp"
#include "components/game/Unit.hpp"

#include "entities/Units.hpp"

#include "utils/Timer.hpp"

#include <iostream>

void moveEnemies(entt::registry &reg)
{
    auto baseView = reg.view<Base>();
    auto enemyView = reg.view<Enemy>();

    const Sprite &baseSprite = reg.get<Sprite>(baseView[0]);

    for (entt::entity enemy : enemyView) {
        const Sprite &enemySprite = reg.get<Sprite>(enemy);
        Movement &movement = reg.get<Movement>(enemy);
        const Vec2d direction = normalize(Vec2d{baseSprite.pos.x - enemySprite.pos.x, baseSprite.pos.y - enemySprite.pos.y});

        movement.direction = direction;
        if (getDistance(baseSprite.pos, enemySprite.pos) < 100) {
            movement.move = false;
        }
        else {
            movement.move = true;
        }
    }
}

void checkEnemyHealth(entt::registry &reg)
{
    auto enemies = reg.view<Enemy, Unit>();

    for (entt::entity e : enemies) {
        const Unit &infos = reg.get<Unit>(e);

        if (infos.health <= 0) {
            reg.destroy(e);
            continue;
        }
    }
}

void spawnEnemies(entt::registry &reg, TexturesLoader &textureLoader, float deltaTime)
{
    static const float spawnRate = 5.f; // in seconds
    static float lastSpawnTime = 0.f;

    if (deltaTime - lastSpawnTime > spawnRate) {
        makeEnemyInfantry(reg, textureLoader, 100, 100);
        lastSpawnTime = deltaTime;
    }
}

void enemySystem(entt::registry &reg)
{
    checkEnemyHealth(reg);
    moveEnemies(reg);
}
