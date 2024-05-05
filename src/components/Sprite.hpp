#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "utils/Vec.hpp"
#include "utils/Rect.hpp"
#include "SDL/Texture.hpp"

struct Sprite {
    bool hidden;
    Vec2f pos;
    Vec2f scale;
    RectI textureRect;
    RectF rect;
    float angle;
    SDL_RendererFlip flip;
    std::shared_ptr<SDL::Texture> texture;
};

#endif // SPRITE_HPP