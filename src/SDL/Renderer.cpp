#include <iostream>
#include "SDL2/SDL2_gfxPrimitives.h"
#include "Renderer.hpp"

using namespace SDL;

Renderer::Renderer() : _renderer(NULL)
{

}

Renderer::Renderer(SDL_Window *window)
{
    initRenderer(window);
}

Renderer::~Renderer()
{
    if (_renderer) {
        SDL_DestroyRenderer(_renderer);
    }
}

SDL_Renderer *Renderer::getRenderer()
{
    return _renderer;
}

void Renderer::initRenderer(SDL_Window *window)
{
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    _renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    setDrawBlendMode(SDL_BLENDMODE_BLEND);
    
    if (_renderer == NULL)
    {
        std::cout << "Error while creating renderer : " <<  SDL_GetError() << std::endl;
        throw "Renderer error";
    };
}

int Renderer::setDrawColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    return SDL_SetRenderDrawColor(_renderer, r, g, b, a);
}

void Renderer::setDrawBlendMode(SDL_BlendMode mode)
{
    SDL_SetRenderDrawBlendMode(_renderer, mode);
}

int Renderer::clear()
{
    return SDL_RenderClear(_renderer);
}

int Renderer::copy(Texture &texture, const SDL_Rect *sourceRect, const SDL_Rect *destRect)
{
    return SDL_RenderCopy(_renderer, texture.getTexture(), sourceRect, destRect);
}

int Renderer::copyEx(Texture &texture,
                     float angle,
                     const SDL_Rect *srcRect,
                     const SDL_Rect *dstRect,
                     SDL_RendererFlip flip)
{
    return SDL_RenderCopyEx(_renderer, texture.getTexture(), srcRect, dstRect, angle, NULL, flip);
}

int Renderer::copyEx(Texture &texture,
                     Vec2i &center,
                     float angle,
                     const SDL_Rect *srcRect,
                     const SDL_Rect *dstRect,
                     SDL_RendererFlip flip)
{
    SDL_Point c(center);
    return SDL_RenderCopyEx(_renderer, texture.getTexture(), srcRect, dstRect, angle, &c, flip);
}

void Renderer::drawRect(const RectI &rect, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    SDL_Rect sdlRect = {
        rect.x,
        rect.y,
        rect.width,
        rect.height
    };
    setDrawColor(r, g, b, a);
    setDrawBlendMode(SDL_BLENDMODE_BLEND); // SDL2_gfx set to no blind if a = 255 sent
    SDL_RenderFillRect(_renderer, &sdlRect);
    setDrawColor(255, 255, 255, 255);
}

void Renderer::drawRect(const RectI &rect, const Color &color)
{
    const SDL_Rect sdlRect = {
        rect.x,
        rect.y,
        rect.width,
        rect.height
    };
    setDrawColor(color.r, color.g, color.b, color.a);
    setDrawBlendMode(SDL_BLENDMODE_BLEND);
    SDL_RenderFillRect(_renderer, &sdlRect);
    setDrawColor(255, 255, 255, 255);
}

void Renderer::drawCircle(int x, int y, int radius, const Color &color)
{
    circleRGBA(_renderer, x, y, radius, color.r, color.g, color.b, color.a);
}

void Renderer::drawFilledCircle(const Vec2f &pos, int16_t radius, const Color &color)
{
    filledCircleRGBA(_renderer, pos.x, pos.y, radius, color.r, color.g, color.b, color.a);
}

void Renderer::drawLine(const Vec2f &a, const Vec2f &b)
{
    SDL_RenderDrawLine(_renderer, a.x, a.y, b.x, b.y);
}

void Renderer::present()
{
    return SDL_RenderPresent(_renderer);
}