#ifndef HUD_TEXT_HPP
#define HUD_TEXT_HPP

#include "HUD/Component.hpp"
#include "SDL/Text.hpp"
#include "utils/Vec.hpp"

namespace HUD
{
    class Text : public Component
    {
    public:
        Text(const std::string &text, SDL::Renderer &renderer, const Vec2i &pos, int fontSize);
        virtual ~Text() = default;

        virtual void draw(SDL::Renderer &renderer);

        void setFontSize(int size);
        void setText(const std::string &text);

    private:
        SDL::Text _text;
    };
}

#endif
