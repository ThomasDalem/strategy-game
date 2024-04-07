#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "utils/Vec.hpp"
#include "utils/Rect.hpp"
#include "SDL/Texture.hpp"

struct Sprite {
    bool hidden;
    Vec2d pos;
    Vec2f scale;
    RectI textureRect;
    RectD rect;
    double angle;
    SDL_RendererFlip flip;
    std::shared_ptr<SDL::Texture> texture;
};

#endif // SPRITE_HPP