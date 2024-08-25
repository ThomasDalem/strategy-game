#include "Zones.hpp"
#include "components/Polygon.hpp"

entt::entity makeWoods(entt::registry &reg, const std::vector<Vec2i> &points)
{
    const entt::entity e = reg.create();

    std::vector<short int> xs;
    std::vector<short int> ys;

    for (const Vec2i &point : points)
    {
        xs.push_back(point.x);
        ys.push_back(point.y);
    }

    Color color {50, 100, 50, 255};
    reg.emplace<Polygon>(e, std::move(xs), std::move(ys), color);
    const int speedFactor = 70;
    const int rangeFactor = 60;
    const bool hide = true;
    reg.emplace<Zone>(e, ZoneType::WOODS, speedFactor, rangeFactor, hide);

    return e;
}

entt::entity makeZone(entt::registry &reg, ZoneType type, const std::vector<Vec2i> &points)
{
    switch (type)
    {
    case ZoneType::WOODS:
        return makeWoods(reg, points);

    default:
        break;
    }
    return entt::null;
}
