#ifndef ZONES_HPP
#define ZONES_HPP

#include <vector>
#include "entt.hpp"
#include "utils/Vec.hpp"
#include "components/Zone.hpp"

entt::entity makeZone(entt::registry &reg, ZoneType type, const std::vector<Vec2i> &points);

#endif
