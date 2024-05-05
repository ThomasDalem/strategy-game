#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "utils/Color.hpp"

struct Circle
{
    Color color;
    float x;
    float y;
    int radius;
    bool filled;
    bool hidden;
};

#endif // CIRCLE_HPP