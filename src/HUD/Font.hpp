#ifndef HUD_FONT_HPP
#define HUD_FONT_HPP

#include "SDL/Font.hpp"

namespace HUD
{
    class Font
    {
    public:
        static Font &getInstance() {
            static Font instance;

            return instance;
        };
        Font(const Font &other) = delete;
        void operator=(const Font &other) = delete;

        SDL::Font &getFont() { return _font; }
    
    private:
        Font() = default;

        SDL::Font _font;
    };
}

#endif