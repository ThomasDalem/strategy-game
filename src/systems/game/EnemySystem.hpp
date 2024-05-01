#ifndef ENEMY_SYSTEM_HPP
#define ENEMY_SYSTEM_HPP

#include "entt.hpp"
#include "utils/TexturesLoader.hpp"

void enemySystem(entt::registry &reg);
void spawnEnemies(entt::registry &reg, TexturesLoader &textureLoader, float deltaTime);

#endif // ENEMY_SYSTEM_HPP
