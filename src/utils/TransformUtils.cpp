#include "TransformUtils.hpp"
#include "components/Relationship.hpp"

void translateCircle(Circle &circle, const Vec2d &translation)
{
    circle.x += translation.x;
    circle.y += translation.y;
}

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

    Circle *circle = reg.try_get<Circle>(e);
    if (circle != nullptr) {
        translateCircle(*circle, translation);
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

void setCirclePosition(Circle &circle, const Vec2d &position)
{
    circle.x = position.x;
    circle.y = position.y;
}

void setSpritePosition(Sprite &sprite, const Vec2d &position, bool centerSprite)
{
    sprite.pos = position;
    sprite.rect.x = sprite.pos.x;
    sprite.rect.y = sprite.pos.y;
    if (centerSprite) {
        const Vec2i &center = sprite.texture->getCenter();
        sprite.pos -= center;
        sprite.rect.x -= center.x;
        sprite.rect.y -= center.y;
    }
}

void setColliderPosition(Collider &collider, const Vec2d &position)
{
    for (Vec2d &vertex : collider.vertices) {
        vertex = position;
    }
}

void setPosition(entt::registry &reg, entt::entity e, const Vec2d &position, bool centerSprites, bool moveChildren)
{
    Sprite *sprite = reg.try_get<Sprite>(e);
    if (sprite != nullptr) {
        setSpritePosition(*sprite, position, centerSprites);
    }

    Collider *collider = reg.try_get<Collider>(e);
    if (collider != nullptr) {
        setColliderPosition(*collider, position);
    }

    Circle *circle = reg.try_get<Circle>(e);
    if (circle != nullptr) {
        setCirclePosition(*circle, position);
    }

    if (moveChildren == false) {
        return;
    }

    auto view = reg.view<Parent>();

    for (entt::entity child : view) {
        const Parent &parent = reg.get<Parent>(child);
        if (parent.parent == e) {
            setPosition(reg, child, position, true);
        }
    }
}
