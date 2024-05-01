#include "MovementSystem.hpp"
#include "components/Movement.hpp"
#include "utils/TransformUtils.hpp"

#include <iostream>

void moveSprites(entt::registry &reg, float deltaTime)
{
    auto view = reg.view<Movement, Sprite>();

    for (const entt::entity e : view) {
        Movement &mov = reg.get<Movement>(e);

        if (mov.move == false) {
            continue;
        }
        const Vec2d posDelta =  (mov.direction * mov.speed) * deltaTime;
        translate(reg, e, posDelta);
    }
}
