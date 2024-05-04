#ifndef UNIT_INFO_HPP
#define UNIT_INFO_HPP

#include "entt.hpp"

enum UnitType
{
    INFANTRY,
    TANK,
    BUILDING,
    BASE
};

struct Unit
{
    UnitType type;
    int health;
    int ammo;
    int range;
    int damage;
    int firerate;
    float lastShotTime;
    entt::entity target;
    bool isActive;
};

#endif // UNIT_INFO_HPP