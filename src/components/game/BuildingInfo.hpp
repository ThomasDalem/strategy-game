#ifndef BUILDING_INFO_HPP
#define BUILDING_INFO_HPP

struct BuildingInfo
{
    int health;
    int ammo;
    int range;
    int damage;
    int firerate;
    uint64_t lastShotTime;
};

#endif // BUILDING_INFO_HPP