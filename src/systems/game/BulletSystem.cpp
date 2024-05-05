#include "BulletSystem.hpp"

void bulletSystem(entt::registry &reg, float deltaTime)
{
    auto view = reg.view<Line, BulletInfo>();

    for (const entt::entity e : view) {
        Line &line = reg.get<Line>(e);
        const BulletInfo &bulletInfo = reg.get<BulletInfo>(e);
        const Vec2f addPos = normalize(bulletInfo.to - bulletInfo.from) * bulletInfo.speed * deltaTime;
        const float distA = getDistance(bulletInfo.from, bulletInfo.to);
        const float distB = getDistance(bulletInfo.from, line.b);
        bool hasBulletHit = false;

        if (distA <= distB)
        {
            line.b = bulletInfo.to; // if the bullet is over the end pos we put it back to the end pos
            hasBulletHit = true;
        }
        else {
            line.b += addPos;
        }

        if (getDistance(line.a, line.b) > 15.f || hasBulletHit)
        {
            line.a += addPos;
            const float distC = getDistance(bulletInfo.from, line.a);
            if (distA <= distC) {
                reg.destroy(e);
            }
        }
    }
}

