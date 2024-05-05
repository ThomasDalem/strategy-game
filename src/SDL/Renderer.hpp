#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
#include "Texture.hpp"
#include "utils/Vec.hpp"
#include "utils/Rect.hpp"
#include "utils/Color.hpp"

namespace SDL {
    
    class Texture;

    class Renderer {
        public:
            Renderer();
            Renderer(SDL_Window *window);
            ~Renderer();

            SDL_Renderer *getRenderer();

            void initRenderer(SDL_Window *window);
            int setDrawColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
            void setDrawBlendMode(SDL_BlendMode mode);
            int clear();
            int copy(Texture &texture, const SDL_Rect *srcRect = NULL, const SDL_Rect *dstRect = NULL);
            int copyEx(Texture &texture,
                       float angle = 0.f,
                       const SDL_Rect *srcRect = NULL,
                       const SDL_Rect *dstRect = NULL,
                       SDL_RendererFlip flip = SDL_FLIP_NONE
            );
            int copyEx(Texture &texture,
                       Vec2i &center,
                       float angle = 0.f,
                       const SDL_Rect *srcRect = NULL,
                       const SDL_Rect *dstRect = NULL,
                       SDL_RendererFlip flip = SDL_FLIP_NONE
            );

            void drawRect(const RectI &rect, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
            void drawCircle(int x, int y, int radius, const Color &color);
            void drawFilledCircle(const Vec2f &pos, int16_t radius, const Color &color);
            void drawLine(const Vec2f &a, const Vec2f &b);

            void present();

        protected:
            SDL_Renderer *_renderer;
    };

}

#endif // RENDERER_HPP