#include "TransformUtils.hpp"
#include "components/Relationship.hpp"

void translatePos(Position &pos, const Vec2f &translation)
{
    pos += translation;
}

void translateSprite(Sprite &sprite, const Vec2f &translation)
{
    sprite.pos += translation;
    sprite.rect.x = sprite.pos.x;
    sprite.rect.y = sprite.pos.y;
}

void translateCircle(Circle &circle, const Vec2f &translation)
{
    circle.x += translation.x;
    circle.y += translation.y;
}

void translateCollider(Collider &collider, const Vec2f &translation)
{
    for (Vec2f &vertex : collider.vertices) {
        vertex += translation;
    }
}

void translate(entt::registry &reg, entt::entity e, const Vec2f &translation, bool moveChildren)
{
    Position &pos = reg.get<Position>(e);
    translatePos(pos, translation);

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

    for (const entt::entity child : view) {
        const Parent &parent = reg.get<Parent>(child);
        if (parent.parent == e) {
            translate(reg, child, translation, true);
        }
    }
}


void setPositionPos(Position &pos, const Vec2f &newPosition)
{
    pos = newPosition;
}

void setSpritePosition(Sprite &sprite, const Vec2f &position, bool centerSprite)
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

void setCirclePosition(Circle &circle, const Vec2f &position)
{
    circle.x = position.x;
    circle.y = position.y;
}

void setColliderPosition(Collider &collider, const Vec2f &position)
{
    for (Vec2f &vertex : collider.vertices) {
        vertex = position;
    }
}

void setPosition(entt::registry &reg, entt::entity e, const Vec2f &position, bool centerSprites, bool moveChildren)
{
    Position &pos = reg.get<Position>(e);
    setPositionPos(pos, position);

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

    const auto view = reg.view<Parent>();

    for (const entt::entity child : view) {
        const Parent &parent = reg.get<Parent>(child);
        if (parent.parent == e) {
            setPosition(reg, child, position, true);
        }
    }
}
