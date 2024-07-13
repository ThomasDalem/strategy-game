#include "HUD/Text.hpp"

using namespace HUD;

Text::Text(const std::string &text, SDL::Renderer &renderer, const Vec2i &pos, int fontSize)
    : Component(pos.x, pos.y)
    , _text(text, renderer, fontSize)
{}

void Text::draw(SDL::Renderer &renderer)
{
    const int width = _text.getTexture().getWidth();
    const int height = _text.getTexture().getHeight();
    SDL_Rect rect {_rect.x, _rect.y, width, height};
    renderer.copy(_text.getTexture(), nullptr, &rect);
}

void Text::setFontSize(int size)
{
    _text.setFontSize(size);
}
