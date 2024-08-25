#ifndef UNIT_SYSTEM_HPP
#define UNIT_SYSTEM_HPP

#include <SDL2/SDL_events.h>
#include "entt.hpp"
#include "components/game/Unit.hpp"
#include "utils/TexturesLoader.hpp"

void makeEngagements(entt::registry &reg, float gameTime);
void dragUnits(entt::registry &reg);
void createUnit(entt::registry &reg, TexturesLoader &textureLoader, UnitType unitType);
void drawHealth(entt::registry &reg, SDL::Renderer &renderer);
void handleInputs(entt::registry &reg, SDL_Event &e);
void moveUnits(entt::registry &reg);
void checkUnitsHealth(entt::registry &reg);
std::string getUnitSoundGroup(const Unit &unit);

#endif // UNIT_SYSTEM_HPP