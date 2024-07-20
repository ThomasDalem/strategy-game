#ifndef BOX_HPP
#define BOX_HPP

#include "HUD/Component.hpp"

namespace HUD
{
    class Box : public Component
    {
    public:
        Box(int x, int y, int width, int height, const Color &color = {255, 255, 255, 255});
        Box(const RectF &rect, const Color &color = {255, 255, 255, 255});

        void setColor(const Color &color);

        void draw(SDL::Renderer &renderer);

    private:
        Color _color;
    };
}

#endif