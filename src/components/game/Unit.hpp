#ifndef UNIT_INFO_HPP
#define UNIT_INFO_HPP

#include "entt.hpp"

#include <array>

enum UnitType
{
    INFANTRY,
    TANK,
    BUILDING,
    BASE
};

static const std::array<int, 4> unitPrices {
    10, 25, 50, 100
};

struct Unit
{
    UnitType type;
    int health;
    int ammo;
    int range;
    int damage;
    int firerate;
    int speed;
    float lastShotTime;
    entt::entity target;
    bool isActive;
};

#endif // UNIT_INFO_HPP