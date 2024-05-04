#ifndef UNIT_SYSTEM_HPP
#define UNIT_SYSTEM_HPP

#include <SDL2/SDL_events.h>
#include "entt.hpp"
#include "utils/TexturesLoader.hpp"

void makeEngagements(entt::registry &reg, float gameTime);
void dragUnits(entt::registry &reg);
void deployUnit(entt::registry &reg, TexturesLoader &textureLoader);
void drawHealth(entt::registry &reg, SDL::Renderer &renderer);
void handleInputs(entt::registry &reg, TexturesLoader &textureLoader, SDL_Event &e);

#endif // UNIT_SYSTEM_HPP