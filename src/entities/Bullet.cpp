#include "Bullet.hpp"

#include "components/Line.hpp"
#include "components/game/BulletInfo.hpp"

void makeBullet(entt::registry &reg, const Vec2f &from, const Vec2f &to, float speed, const std::string &destroySound)
{
    const entt::entity e = reg.create();

    reg.emplace<BulletInfo>(e, from, to, speed, destroySound);

    const Vec2f lineEnd = from + normalize(Vec2f{to.x - from.x, to.y - from.y}) * 30;

    reg.emplace<Line>(e, from, lineEnd, false);
}
