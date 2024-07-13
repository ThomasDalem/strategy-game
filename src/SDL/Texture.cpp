#include <iostream>
#include "Texture.hpp"
#include "Surface.hpp"

using namespace SDL;

Texture::Texture() : _texture(nullptr), _width(-1), _height(-1), _isLoaded(false)
{}

Texture::Texture(const std::string& path, Renderer& renderer) :
    _texture(nullptr),
    _width(-1),
    _height(-1),
    _isLoaded(false)
{
    Surface surface(path);

    loadFromSurface(surface, renderer);
}

Texture::Texture(SDL_Texture *texture)
{
    _texture = texture;
    if (SDL_QueryTexture(_texture, NULL, NULL, &_width, &_height) < 0) {
        std::cout << "Error while getting information on texture: " << SDL_GetError() << "\n";
    }
    _isLoaded = true;
}

Texture::Texture(Surface &surface, Renderer &renderer)
{
    loadFromSurface(surface, renderer);
}

Texture::~Texture()
{
    if (_texture) {
        SDL_DestroyTexture(_texture);
    }
}

void Texture::loadFromSurface(Surface &surface, Renderer &renderer)
{
    if (!surface.isLoaded()) {
        std::cout << "Error: texture not loaded because surface is not loaded\n";
        return;
    }
    _texture = SDL_CreateTextureFromSurface(renderer.getRenderer(), surface.getSurface());
    if (_texture == NULL) {
        std::cout << "Error: could not create texture: " << SDL_GetError() << "\n";
        return;
    }
    if (SDL_QueryTexture(_texture, NULL, NULL, &_width, &_height) < 0) {
        std::cout << "Error while getting information on texture: " << SDL_GetError() << "\n";
    }
    _isLoaded = true;
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

void Texture::operator=(SDL_Texture *texture)
{
    _texture = texture;
    if (SDL_QueryTexture(_texture, NULL, NULL, &_width, &_height) < 0) {
        std::cout << "Error while getting information on texture: " << SDL_GetError() << "\n";
    }
    _isLoaded = true;
}
