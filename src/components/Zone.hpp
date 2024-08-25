#ifndef ZONE_HPP
#define ZONE_HPP 

enum ZoneType {
    PLAINS,
    WOODS,
    HILL,
    CITY
};

struct Zone
{
    ZoneType type;
    int speedFactor;
    int rangeFactor;
    bool hide;
};

#endif
