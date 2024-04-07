#ifndef INFANTRY_HPP
#define INFANTRY_HPP

#include "entt.hpp"
#include "utils/TexturesLoader.hpp"

entt::entity makeInfantry(entt::registry &reg, TexturesLoader &textureLoader, double x, double y);

#endif // INFANTRY_HPP