#ifndef BUILDING_HPP
#define BUILDING_HPP

#include "entt.hpp"
#include "utils/TexturesLoader.hpp"

entt::entity makeMachineGun(entt::registry &reg, TexturesLoader &textureLoader, double x, double y);
entt::entity makeBase(entt::registry &reg, TexturesLoader &textureLoader, double x, double y);

#endif // BUILDING_HPP