#ifndef MOVEMENT_HPP
#define MOVEMENT_HPP

#include "utils/Vec.hpp"

struct Movement
{
    Vec2d direction;
    double speed;
    bool move;
};

#endif // MOVEMENT_HPP