#ifndef UNIT_INFO_HPP
#define UNIT_INFO_HPP

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
    bool isActive;
};

#endif // UNIT_INFO_HPP