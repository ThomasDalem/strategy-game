#include "SDL/Text.hpp"
#include "HUD/Font.hpp"

using namespace SDL;

Text::Text(const std::string &text, SDL::Renderer &renderer, int fontSize) 
    : _text(text)
    , _renderer(renderer)
{
    SDL::Font &font = HUD::Font::getInstance().getFont();

    if (font.isLoaded() == false) {
        font.loadFont("../assets/font.ttf", fontSize);
    }
    _surface = TTF_RenderText_Solid(font.getFont(), text.c_str(), {255, 255, 255, 255});
    _texture.loadFromSurface(_surface, renderer);
}

void Text::setText(const std::string &text)
{
    _text = text;
    SDL::Font &font = HUD::Font::getInstance().getFont();
    
    if (font.isLoaded() == false) {
        font.loadFont("../assets/font.ttf", 24);
    }
    _surface = TTF_RenderText_Solid(font.getFont(), _text.c_str(), {255, 255, 255, 255});
    _texture.loadFromSurface(_surface, _renderer);
}

void Text::setFontSize(int size)
{
    SDL::Font &font = HUD::Font::getInstance().getFont();

    if (font.isLoaded() == false) {
        font.loadFont("../assets/font.ttf", size);
    }
    else {
        font.setSize(size);
    }
    _surface = TTF_RenderText_Solid(font.getFont(), _text.c_str(), {255, 255, 255, 255});
    _texture.loadFromSurface(_surface, _renderer);
}

const std::string &Text::getText() const
{
    return _text;
}

Texture &Text::getTexture()
{
    return _texture;
}
