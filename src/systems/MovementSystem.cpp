#include "MovementSystem.hpp"
#include "components/Movement.hpp"
#include "utils/TransformUtils.hpp"

void moveSprites(entt::registry &reg, uint32_t deltaTime)
{
    auto view = reg.view<Movement, Sprite>();

    if (deltaTime < 1) {
        deltaTime = 1; // To prevent product by 0 when frametime is lower than 1ms
    }
    for (const entt::entity e : view) {
        Movement &mov = reg.get<Movement>(e);

        Vec2d posDelta = mov.direction * mov.speed * deltaTime;
        if (posDelta.x && posDelta.y) {
            posDelta.x /= 2.0;
            posDelta.y /= 2.0;
        }
        translate(reg, e, posDelta);
    }
}
