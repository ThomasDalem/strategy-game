#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "utils/Color.hpp"

struct Circle
{
    Color color;
    double x;
    double y;
    int radius;
    bool hidden;
};

#endif // CIRCLE_HPP