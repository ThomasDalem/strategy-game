#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "utils/Rect.hpp"
#include <SDL2/SDL.h>

struct Rectangle {
    RectI rect;
    SDL_Color color = {255, 255, 255, 50};
    bool hidden = false;
};

#endif // RECTANGLE_HPP