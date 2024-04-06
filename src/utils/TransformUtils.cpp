#include "TransformUtils.hpp"
#include "components/Collider.hpp"
#include "components/Relationship.hpp"

void translateSprite(Sprite &sprite, const Vec2d &translation)
{
    sprite.pos += translation;
    sprite.rect.x = sprite.pos.x;
    sprite.rect.y = sprite.pos.y;
}

void translateCollider(Collider &collider, const Vec2d &translation)
{
    for (Vec2d &vertex : collider.vertices) {
        vertex += translation;
    }
}

void translate(entt::registry &reg, entt::entity e, const Vec2d &translation, bool moveChildren)
{
    Sprite *sprite = reg.try_get<Sprite>(e);
    if (sprite != nullptr) {
        translateSprite(*sprite, translation);
    }

    Collider *collider = reg.try_get<Collider>(e);
    if (collider != nullptr) {
        translateCollider(*collider, translation);
    }

    if (moveChildren == false) {
        return;
    }

    auto view = reg.view<Parent>();

    for (entt::entity child : view) {
        const Parent &parent = reg.get<Parent>(child);
        if (parent.parent == e) {
            translate(reg, child, translation, true);
        }
    }
}
