#ifndef UNIT_INFO_HPP
#define UNIT_INFO_HPP

#include "entt.hpp"

#include <array>

enum UnitType
{
    INFANTRY,
    ARMORED,
    BUILDING,
    BASE
};

static const std::array<int, 4> unitPrices {
    10, 100, 50, 100
};

struct Unit
{
    UnitType type;
    int health;
    int totalHealth;
    int ammo;
    int baseRange;
    int range;
    int damage;
    int firerate;
    int baseSpeed;
    int speed;
    float lastShotTime;
    entt::entity target;
    bool isHidden;
};

#endif // UNIT_INFO_HPP