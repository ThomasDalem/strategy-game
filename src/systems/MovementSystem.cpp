#include "MovementSystem.hpp"

#include "utils/TransformUtils.hpp"
#include "components/Movement.hpp"
#include "components/game/Waypoint.hpp"

void moveObjects(entt::registry &reg, float deltaTime)
{
    const auto view = reg.view<Movement, Position>();

    for (const entt::entity e : view) {
        const Movement &mov = reg.get<Movement>(e);

        if (mov.move == false) {
            continue;
        }
        const Vec2f posDelta = mov.direction * mov.speed * deltaTime;
        Waypoint *wp = reg.try_get<Waypoint>(e);
        if (wp != nullptr) {
            const Position &pos = reg.get<Position>(e);
            const float distance = getDistance(pos, wp->pos);
            const float newDistance = getDistance(pos, pos + posDelta);
            if (distance < newDistance) {
                setPosition(reg, e, wp->pos);
                reg.remove<Waypoint>(e);
                reg.remove<Movement>(e);
                return;
            }
        }
        translate(reg, e, posDelta);
    }
}
