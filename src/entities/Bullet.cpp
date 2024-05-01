#include "Bullet.hpp"

#include "components/Line.hpp"
#include "components/game/BulletInfo.hpp"

void makeBullet(entt::registry &reg, const Vec2d &from, const Vec2d &to, double speed)
{
    const entt::entity e = reg.create();

    reg.emplace<BulletInfo>(e, from, to, speed);

    const Vec2d lineEnd = from + normalize(Vec2d{to.x - from.x, to.y - from.y}) * 30;

    reg.emplace<Line>(e, from, lineEnd, false);
}
