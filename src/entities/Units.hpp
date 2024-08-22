#ifndef UNITS_HPP
#define UNITS_HPP

#include "entt.hpp"
#include "utils/TexturesLoader.hpp"

// Buildings

entt::entity makeBase(entt::registry &reg, TexturesLoader &textureLoader, float x, float y);

// Allied units

entt::entity makeAlliedInfantry(entt::registry &reg, TexturesLoader &textureLoader, float x, float y);
entt::entity makeFriendlyArmored(entt::registry &reg, TexturesLoader &textureLoader, float x, float y);

// Enemy units

entt::entity makeEnemyInfantry(entt::registry &reg, TexturesLoader &textureLoader, float x, float y);
entt::entity makeHostileArmored(entt::registry &reg, TexturesLoader &textureLoader, float x, float y);

#endif // UNITS_HPP