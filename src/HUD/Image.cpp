#include <iostream>
#include "Image.hpp"
#include "utils/TexturesLoader.hpp"

using namespace HUD;

Image::Image(const std::string &filepath, TexturesLoader &textureLoader, int x, int y)
    : Component(x, y)
    , _texture(textureLoader.getTexture(filepath))
{
    _rect.width = _texture->getWidth();
    _rect.height = _texture->getHeight();
}

Image::Image(const std::shared_ptr<SDL::Texture> &texture, int x, int y)
    : Component(x, y), _texture(texture)
{}

void Image::draw(SDL::Renderer &renderer)
{
    if (_texture == nullptr) {
        std::cerr << "Trying to draw HUD::Image with null texture\n";
        return;
    }
    const SDL_Rect rect = {
        _rect.x,
        _rect.y,
        _texture->getWidth(),
        _texture->getHeight()
    };
    renderer.copy(*_texture, nullptr, &rect);
}

Vec2i Image::getCenter() const
{
    return _texture->getCenter();
}
