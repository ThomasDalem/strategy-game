#include <iostream>
#include <cmath>

#include "CollisionSystem.hpp"
#include "components/Collider.hpp"
#include "components/Sprite.hpp"
#include "utils/Rect.hpp"
#include "utils/TransformUtils.hpp"

Vec2d getPolygonCenter(const std::vector<Vec2d> &vertices)
{
    Vec2d center = {0.0, 0.0};

    for (const Vec2d &vertex : vertices) {
        center += vertex;
    }

    return {center.x / vertices.size(), center.y / vertices.size()};
}

Vec2d normalize(const Vec2d &v)
{
    const double length = std::sqrt(v.x * v.x + v.y * v.y);
    return {v.x / length, v.y / length};
}

std::vector<Vec2d> getAxes(const std::vector<Vec2d> &vertices)
{
    std::vector<Vec2d> axes; // TODO: check for parallel axes
    for (size_t i = 0; i < vertices.size(); i++) {
        const Vec2d p1 = vertices[i];
        const int p2Index = i + 1 == vertices.size() ? 0 : i + 1; // Get the first index if we are at the last one
        const Vec2d p2 = vertices[p2Index];
        const Vec2d edge = p1 - p2;
        const Vec2d normal = {-edge.y, edge.x};
        axes.push_back(normalize(normal));
    }
    return axes;
}

double dotProduct(const Vec2d &a, const Vec2d &b)
{
    return a.x * b.x + a.y * b.y;
}

Vec2d getProjection(const Vec2d &axe, const std::vector<Vec2d> &vertices)
{
    double min = std::numeric_limits<double>::infinity();
    double max = -std::numeric_limits<double>::infinity();

    for (size_t i = 0; i < vertices.size(); i++) {
        const double p = dotProduct(axe, vertices[i]);
        if (p < min) {
            min = p;
        }
        if (p > max) {
            max = p;
        }
    }

    return {min, max};
}

bool areOverlapping(const Vec2d &a, const Vec2d &b)
{
    return a.x <= b.y && a.y >= b.x;
}

double getOverlapLength(const Vec2d &a, const Vec2d &b)
{
    return std::abs(std::min(a.y, b.y) - std::max(a.x, b.x));
}

bool isColliding(const std::vector<Vec2d> &a, const std::vector<Vec2d> &b, Vec2d &mtv)
{
    std::vector<Vec2d> axes = getAxes(a);
    std::vector<Vec2d> axesB = getAxes(b);
    axes.insert(axes.end(), axesB.begin(), axesB.end());
    double minOverlap = std::numeric_limits<double>::infinity();

    for (const Vec2d &axis : axes) {
        Vec2d proj1 = getProjection(axis, a);
        Vec2d proj2 = getProjection(axis, b);

        if (areOverlapping(proj1, proj2) == false) {
            return false;
        }
        else {
            double overlapLength = getOverlapLength(proj1, proj2);
            if (overlapLength < minOverlap) {
                minOverlap = overlapLength;
                mtv = axis * minOverlap;
            }
        }
    }

    return true;
}

void moveCollider(std::vector<Vec2d> &vertices, const Vec2d &length)
{
    for (Vec2d &vertex : vertices) {
        vertex += length;
    }
}

void moveSprite(const Vec2d &length, entt::registry &reg, entt::entity e)
{
    Sprite *sprite = reg.try_get<Sprite>(e);
    if (sprite == nullptr) {
        return;
    }
    sprite->pos += length;
    sprite->rect.x += length.x;
    sprite->rect.y += length.y;
}

Vec2d testSub(const Vec2d &a, const Vec2d &b)
{
    return {a.x - b.x, a.y - b.y};
}

void handleCollisions(entt::registry &reg)
{
    auto view = reg.view<Collider>();

    for (const entt::entity e : view) {
        Collider &collider = reg.get<Collider>(e);

        for (const entt::entity other : view) {
            if (e == other) {
                continue;
            }
            Collider &otherCollider = reg.get<Collider>(other);
            Vec2d mtv;

            if (collider.canMove && isColliding(collider.vertices, otherCollider.vertices, mtv)) {
                collider.drawColor = {255, 0, 0, 0};
                otherCollider.drawColor = {255, 0, 0, 0};

                const Vec2d centerA = getPolygonCenter(collider.vertices);
                const Vec2d centerB = getPolygonCenter(otherCollider.vertices);

                if (dotProduct(centerA - centerB, mtv) < 0.0) {
                    mtv = {-mtv.x, -mtv.y};
                }

                translate(reg, e, mtv);
            }
            else {
                collider.drawColor = {255, 255, 255, 0};
                otherCollider.drawColor = {255, 255, 255, 0};
            }
        }
    }
}
