#include "EnemyMovement.hpp"
#include "components/tags/Base.hpp"
#include "components/Movement.hpp"
#include "components/game/Enemy.hpp"
#include "components/Sprite.hpp"

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
