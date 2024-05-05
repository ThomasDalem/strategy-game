#ifndef TRANSFORM_UTILS_HPP
#define TRANSFORM_UTILS_HPP

#include "entt.hpp"
#include "Vec.hpp"

#include "components/Position.hpp"
#include "components/Sprite.hpp"
#include "components/Collider.hpp"
#include "components/Circle.hpp"

void translatePos(Position &pos, const Vec2f &translation);
void translateSprite(Sprite &sprite, const Vec2f &translation);
void translateCircle(Circle &circle, const Vec2f &translation);
void translateCollider(Collider &collider, const Vec2f &translation);
void translate(entt::registry &reg, entt::entity e, const Vec2f &translation, bool moveChildren = true);

void setPositionPos(Position &pos, const Vec2f &newPosition);
void setSpritePosition(Sprite &sprite, const Vec2f &position, bool centerSprite);
void setCirclePosition(Circle &circle, const Vec2f &position);
void setColliderPosition(Collider &collider, const Vec2f &position);
void setPosition(entt::registry &reg, entt::entity e, const Vec2f &position, bool centerSprites = true, bool moveChildren = true);

#endif // TRANSFORM_UTILS_HPP