#ifndef COLLIDER_HPP
#define COLLIDER_HPP

#include <vector>
#include "utils/Vec.hpp"
#include "SDL2/SDL_pixels.h"

struct Collider
{
    std::vector<Vec2f> vertices;
    bool display;
    bool canMove = false;
    SDL_Color drawColor {255, 255, 255, 0};
};


#endif // COLLIDER_HPP