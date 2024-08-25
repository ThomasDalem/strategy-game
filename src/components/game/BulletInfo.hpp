#ifndef BULLET_INFO_HPP
#define BULLET_INFO_HPP

#include <string>
#include "utils/Vec.hpp"

struct BulletInfo
{
    Vec2f from;
    Vec2f to;
    float speed;
    std::string destroySound;
};

#endif // BULLET_INFO_HPP
