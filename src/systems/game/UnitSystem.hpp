#ifndef UNIT_SYSTEM_HPP
#define UNIT_SYSTEM_HPP

#include <SDL2/SDL_events.h>
#include "entt.hpp"
#include "utils/TexturesLoader.hpp"

void shootEnemies(entt::registry &reg, uint64_t gameTime);
void dragUnits(entt::registry &reg);
void deployUnit(entt::registry &reg, TexturesLoader &textureLoader);
void handleInputs(entt::registry &reg, TexturesLoader &textureLoader, SDL_Event &e);

#endif // UNIT_SYSTEM_HPP