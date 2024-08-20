#ifndef SDL_TEXT_HPP
#define SDL_TEXT_HPP

#include <string>
#include <memory>
#include <SDL2/SDL_ttf.h>

#include "SDL/Surface.hpp"
#include "SDL/Texture.hpp"

namespace SDL
{
    class Text
    {
    public:
        Text() = default;
        Text(const std::string &text, SDL::Renderer &renderer, int fontSize);

        void setText(const std::string &string);
        void setFontSize(int size);

        const std::string &getText() const;
        Texture &getTexture();
        inline int getFontSize() const;

    private:
        std::string _text;
        Surface _surface;
        Texture _texture;
        SDL::Renderer &_renderer;
        int _fontSize;
    };
}

#endif