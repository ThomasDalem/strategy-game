#ifndef DYNAMIC_TEXT_HPP
#define DYNAMIC_TEXT_HPP

#include "HUD/Text.hpp"
#include <sstream>

namespace HUD
{
    template<typename T>
    class DynamicText : public Text
    {
    public:
        DynamicText(T *value, SDL::Renderer &renderer, const Vec2i &pos, int fontSize)
            : Text("", renderer, pos, fontSize)
            , value(value)
        {
            std::stringstream ss;
            ss << *value;
            _oldText = ss.str();
            setText(_oldText);
        }

        void draw(SDL::Renderer &renderer)
        {
            std::stringstream ss;
            ss << *value;
            const std::string newText = ss.str();
            if (newText == _oldText) {
                Text::draw(renderer);
                return;
            }
            setText(newText);
            _oldText = newText;
            Text::draw(renderer);
        }

    private:
        T *value;
        std::string _oldText;
    };
} 

#endif