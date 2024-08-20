#ifndef FONT_HPP
#define FONT_HPP

#include <SDL2/SDL_ttf.h>
#include <string>

namespace SDL
{
    class Font
    {
    public:
        Font();
        ~Font();

        void loadFont(const std::string &filepath, int size);
        void setSize(int size);
        TTF_Font *getFont();
        int getSize() const;
        bool isLoaded() const;

    private:
        TTF_Font *_font;
        int _size;
    };
}

#endif