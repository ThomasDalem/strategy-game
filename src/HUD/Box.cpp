#include "HUD/Box.hpp"

using namespace HUD;

Box::Box(int x, int y, int width, int height, const Color &color)
    : Component(x, y, width, height)
    , _color(color)
{}

Box::Box(const RectI &rect, const Color &color)
    : Component(rect.x, rect.y, rect.width, rect.height)
    , _color(color)
{}

void Box::setColor(const Color &color)
{
    _color = color;
}

void Box::draw(SDL::Renderer &renderer)
{
    renderer.drawRect(_rect, _color);
}
