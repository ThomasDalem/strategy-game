#ifndef UNIT_INFO_HPP
#define UNIT_INFO_HPP

#include "Unit.hpp"

struct UnitInfo
{
    UnitType type;
    int health;
    int ammo;
    int range;
    int damage;
    int firerate;
    uint64_t lastShotTime;
};

#endif // UNIT_INFO_HPP