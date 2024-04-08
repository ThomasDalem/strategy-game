#include "MovementSystem.hpp"
#include "components/Movement.hpp"
#include "utils/TransformUtils.hpp"

void moveSprites(entt::registry &reg, uint64_t deltaTime)
{
    auto view = reg.view<Movement, Sprite>();

    if (deltaTime < 1) { // TODO : not precise enough, need to change this
        deltaTime = 1; // To prevent product by 0 when frametime is lower than 1ms
    }
    for (const entt::entity e : view) {
        Movement &mov = reg.get<Movement>(e);

        if (mov.move == false) {
            continue;
        }
        const Vec2d posDelta = mov.direction * mov.speed * static_cast<double>(deltaTime);
        translate(reg, e, posDelta);
    }
}
