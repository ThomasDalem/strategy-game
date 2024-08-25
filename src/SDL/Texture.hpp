#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>
#include <cstdint>
#include <SDL2/SDL.h>

#include "Renderer.hpp"
#include "utils/Vec.hpp"
#include "Surface.hpp"

namespace SDL
{
    class Renderer;

    class Texture {
    public:
        Texture();
        Texture(const std::string &path, Renderer &renderer);
        Texture(SDL_Texture *texture);
        Texture(Surface &surface, Renderer &renderer);
        ~Texture();

        void loadFromSurface(Surface &surface, Renderer &renderer);

        SDL_Texture *getTexture();
        int getWidth() const;
        int getHeight() const;
        Vec2i getCenter() const;
        bool isLoaded() const;

        void setAlpha(std::uint8_t alpha);

        void operator=(SDL_Texture *texture);

    private:
        SDL_Texture *_texture;
        int _width;
        int _height;
        bool _isLoaded;
    };
    
}

#endif // TEXTURE_HPP