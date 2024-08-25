#ifndef BULLET_HPP
#define BULLET_HPP

#include "entt.hpp"
#include "utils/Vec.hpp"

void makeBullet(entt::registry &reg, const Vec2f &from, const Vec2f &to, float speed, const std::string &destroySound = "");

#endif // BULLET_HPP