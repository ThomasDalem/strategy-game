#ifndef LINE_HPP
#define LINE_HPP

#include "utils/Vec.hpp"

struct Line
{
    Vec2d a;
    Vec2d b;
    bool hidden;
};

#endif // LINE_HPP