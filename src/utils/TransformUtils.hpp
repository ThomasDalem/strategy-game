#ifndef TRANSFORM_UTILS_HPP
#define TRANSFORM_UTILS_HPP

#include "entt.hpp"
#include "Vec.hpp"

#include "components/Position.hpp"
#include "components/Sprite.hpp"
#include "components/Collider.hpp"
#include "components/Circle.hpp"

void translateCircle(Circle &circle, const Vec2d &translation);
void translateSprite(Sprite &sprite, const Vec2d &translation);
void translateCollider(Collider &collider, const Vec2d &translation);
void translate(entt::registry &reg, entt::entity e, const Vec2d &translation, bool moveChildren = true);

void setCirclePosition(Circle &circle, const Vec2d &position);
void setSpritePosition(Sprite &sprite, const Vec2d &position, bool centerSprite);
void setColliderPosition(Collider &collider, const Vec2d &position);
void setPosition(entt::registry &reg, entt::entity e, const Vec2d &position, bool centerSprites = true, bool moveChildren = true);

#endif // TRANSFORM_UTILS_HPP