#ifndef UNITS_HPP
#define UNITS_HPP

#include "entt.hpp"
#include "utils/TexturesLoader.hpp"

// Buildings

entt::entity makeBase(entt::registry &reg, TexturesLoader &textureLoader, double x, double y);

// Allied units

entt::entity makeAlliedInfantry(entt::registry &reg, TexturesLoader &textureLoader, double x, double y);

// Enemy units

entt::entity makeEnemyInfantry(entt::registry &reg, TexturesLoader &textureLoader, double x, double y);

#endif // UNITS_HPP