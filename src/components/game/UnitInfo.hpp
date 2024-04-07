#ifndef UNIT_INFO_HPP
#define UNIT_INFO_HPP

struct UnitInfo
{
    int health;
    int ammo;
    int range;
    int damage;
    int firerate;
    uint64_t lastShotTime;
};

#endif // UNIT_INFO_HPP