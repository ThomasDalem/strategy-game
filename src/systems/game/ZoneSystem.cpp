#include "ZoneSystem.hpp"

#include <iostream>

#include "components/game/Unit.hpp"
#include "components/Position.hpp"
#include "components/Polygon.hpp"
#include "components/Zone.hpp"
#include "components/Sprite.hpp"

bool isIntersecting(int ax, int ay, int bx, int by, const Position &pos)
{
    if (pos.x == ax && pos.y == ay)
    {
        return true;
    }
    if ((ay > pos.y) != (by > pos.y))
    {
        const float slope = (pos.x - ax) * (by - ay) - (bx - ax) * (pos.y - ay);
        if (slope == 0.f)
        {
            return true;
        }
        if ((slope < 0.f) != (by < ay))
        {
            return true;
        }
    }
    return false;
}

bool isInsidePolygon(const Polygon &polygon, const Position &pos)
{
    bool isInside = false;
    for (std::size_t i = 1; i < polygon.xs.size(); i++)
    {
        const int ax = polygon.xs[i];
        const int ay = polygon.ys[i];
        const int bx = polygon.xs[i - 1];
        const int by = polygon.ys[i - 1];

        if (isIntersecting(ax, ay, bx, by, pos))
        {
            isInside = !isInside;
        }
    }

    const int ax = polygon.xs[0];
    const int ay = polygon.ys[0];
    const int bx = polygon.xs[polygon.xs.size() - 1];
    const int by = polygon.ys[polygon.ys.size() - 1];
    if (isIntersecting(ax, ay, bx, by, pos)) // for the last 2 points
    {
        isInside = !isInside;
    }
    return isInside;
}

void ZoneSystem(entt::registry &reg)
{
    const auto posView = reg.view<Unit, Position, Sprite>();
    const auto polyView = reg.view<Polygon, Zone>();

    for (const entt::entity unitEntity : posView)
    {
        const Position &pos = reg.get<Position>(unitEntity);
        Sprite &sprite = reg.get<Sprite>(unitEntity);
        Unit &unit = reg.get<Unit>(unitEntity);

        for (const entt::entity zoneEntity : polyView)
        {
            const Polygon &polygon = reg.get<Polygon>(zoneEntity);
            const Zone &zone = reg.get<Zone>(zoneEntity);

            if (isInsidePolygon(polygon, pos))
            {
                if (zone.hide && !unit.isHidden)
                {
                    sprite.alpha = 110;
                    unit.isHidden = true;
                    unit.speed *= static_cast<float>(zone.rangeFactor) / 100.f;
                    unit.range *= static_cast<float>(zone.rangeFactor) / 100.f;
                }
            }
            else
            {
                sprite.alpha = 255;
                unit.isHidden = false;
                unit.speed = unit.baseSpeed;
                unit.range = unit.baseRange;
            }
        }
    }
}

