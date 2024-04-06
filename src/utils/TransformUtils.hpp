#ifndef TRANSFORM_UTILS_HPP
#define TRANSFORM_UTILS_HPP

#include "entt.hpp"
#include "Vec.hpp"

#include "components/Position.hpp"
#include "components/Sprite.hpp"
#include "components/Collider.hpp"

void translateSprite(Sprite &sprite, const Vec2d &translation);
void translateCollider(Collider &collider, const Vec2d &translation);
void translate(entt::registry &reg, entt::entity e, const Vec2d &translation, bool moveChildren = true);

#endif // TRANSFORM_UTILS_HPP