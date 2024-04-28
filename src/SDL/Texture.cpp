#include <iostream>
#include "Texture.hpp"
#include "Surface.hpp"

using namespace SDL;

Texture::Texture(const std::string& path, Renderer& renderer) :
    _width(-1),
    _height(-1),
    _isLoaded(false),
    _texture(nullptr)
{
    Surface surface(path);

    if (!surface.isLoaded()) {
        std::cout << "Error: texture not loaded because surface is not loaded" << std::endl;
        return;
    }
    _texture = SDL_CreateTextureFromSurface(renderer.getRenderer(), surface.getSurface());
    if (_texture == NULL) {
        std::cout << "Error: could not create texture: " << SDL_GetError() << std::endl;
        return;
    }
    if (SDL_QueryTexture(_texture, NULL, NULL, &_width, &_height) < 0) {
        std::cout << "Error while getting information on texture: " << SDL_GetError() << std::endl;
    }
    _isLoaded = true;
}

Texture::~Texture()
{
    if (_texture) {
        SDL_DestroyTexture(_texture);
    }
}

SDL_Texture *Texture::getTexture()
{
    return _texture;
}

int Texture::getWidth() const
{
    return _width;
}

int Texture::getHeight() const
{
    return _height;
}

Vec2i Texture::getCenter() const
{
    return {_width / 2, _height / 2};
}

bool Texture::isLoaded() const
{
    return _isLoaded;
}
