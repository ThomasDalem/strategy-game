#include <iostream>
#include <cmath>

#include "CollisionSystem.hpp"
#include "components/Collider.hpp"
#include "components/Sprite.hpp"
#include "utils/Rect.hpp"
#include "utils/TransformUtils.hpp"

Vec2f getPolygonCenter(const std::vector<Vec2f> &vertices)
{
    Vec2f center = {0.f, 0.f};

    for (const Vec2f &vertex : vertices) {
        center += vertex;
    }

    return {center.x / vertices.size(), center.y / vertices.size()};
}

Vec2f normalize(const Vec2f &v)
{
    const float length = std::sqrt(v.x * v.x + v.y * v.y);
    return {v.x / length, v.y / length};
}

std::vector<Vec2f> getAxes(const std::vector<Vec2f> &vertices)
{
    std::vector<Vec2f> axes; // TODO: check for parallel axes
    for (size_t i = 0; i < vertices.size(); i++) {
        const Vec2f p1 = vertices[i];
        const int p2Index = i + 1 == vertices.size() ? 0 : i + 1; // Get the first index if we are at the last one
        const Vec2f p2 = vertices[p2Index];
        const Vec2f edge = p1 - p2;
        const Vec2f normal = {-edge.y, edge.x};
        axes.push_back(normalize(normal));
    }
    return axes;
}

float dotProduct(const Vec2f &a, const Vec2f &b)
{
    return a.x * b.x + a.y * b.y;
}

Vec2f getProjection(const Vec2f &axe, const std::vector<Vec2f> &vertices)
{
    float min = std::numeric_limits<float>::infinity();
    float max = -std::numeric_limits<float>::infinity();

    for (size_t i = 0; i < vertices.size(); i++) {
        const float p = dotProduct(axe, vertices[i]);
        if (p < min) {
            min = p;
        }
        if (p > max) {
            max = p;
        }
    }

    return {min, max};
}

bool areOverlapping(const Vec2f &a, const Vec2f &b)
{
    return a.x <= b.y && a.y >= b.x;
}

float getOverlapLength(const Vec2f &a, const Vec2f &b)
{
    return std::abs(std::min(a.y, b.y) - std::max(a.x, b.x));
}

bool isColliding(const std::vector<Vec2f> &a, const std::vector<Vec2f> &b, Vec2f &mtv)
{
    std::vector<Vec2f> axes = getAxes(a);
    std::vector<Vec2f> axesB = getAxes(b);
    axes.insert(axes.end(), axesB.begin(), axesB.end());
    float minOverlap = std::numeric_limits<float>::infinity();

    for (const Vec2f &axis : axes) {
        Vec2f proj1 = getProjection(axis, a);
        Vec2f proj2 = getProjection(axis, b);

        if (areOverlapping(proj1, proj2) == false) {
            return false;
        }
        else {
            const float overlapLength = getOverlapLength(proj1, proj2);
            if (overlapLength < minOverlap) {
                minOverlap = overlapLength;
                mtv = axis * minOverlap;
            }
        }
    }

    return true;
}

void moveCollider(std::vector<Vec2f> &vertices, const Vec2f &length)
{
    for (Vec2f &vertex : vertices) {
        vertex += length;
    }
}

void moveSprite(const Vec2f &length, entt::registry &reg, entt::entity e)
{
    Sprite *sprite = reg.try_get<Sprite>(e);
    if (sprite == nullptr) {
        return;
    }
    sprite->pos += length;
    sprite->rect.x += length.x;
    sprite->rect.y += length.y;
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
            Vec2f mtv;

            if (collider.canMove && isColliding(collider.vertices, otherCollider.vertices, mtv)) {
                collider.drawColor = {255, 0, 0, 0};
                otherCollider.drawColor = {255, 0, 0, 0};

                const Vec2f centerA = getPolygonCenter(collider.vertices);
                const Vec2f centerB = getPolygonCenter(otherCollider.vertices);

                if (dotProduct(centerA - centerB, mtv) < 0.f) {
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
