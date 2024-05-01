#ifndef BULLET_HPP
#define BULLET_HPP

#include "entt.hpp"
#include "utils/Vec.hpp"

void makeBullet(entt::registry &reg, const Vec2d &from, const Vec2d &to, double speed);

#endif // BULLET_HPP