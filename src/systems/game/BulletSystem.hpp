#ifndef BULLET_SYSTEM_HPP
#define BULLET_SYSTEM_HPP

#include "entt.hpp"

#include "components/Line.hpp"
#include "components/game/BulletInfo.hpp"

void bulletSystem(entt::registry &reg, float deltaTime);

#endif // BULLET_SYSTEM_HPP