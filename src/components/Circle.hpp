#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "utils/Color.hpp"

struct Circle
{
    Color color;
    int x;
    int y;
    int radius;
    bool hidden;
};

#endif // CIRCLE_HPP