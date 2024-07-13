#include <iostream>
#include <SDL_image.h>

#include "Surface.hpp"

using namespace SDL;

Surface::Surface() : _surface(nullptr), _isLoaded(false)
{}

Surface::Surface(const std::string &filepath, SDL_Surface *winSurface) : _surface(nullptr), _isLoaded(false)
{
    if (filepath.empty()) {
        return;
    }
    SDL_Surface *tmp = NULL;
    tmp = IMG_Load(filepath.c_str());
    if (tmp == NULL) {
        std::cout << "Error: could not load " << filepath << " " << IMG_GetError() << std::endl;
        return;
    }
    if (winSurface == NULL) {
        _surface = tmp;
    }
    else {
        _surface = SDL_ConvertSurface(tmp, winSurface->format, 0);
        SDL_FreeSurface(tmp);
    }
    _isLoaded = true;
}

Surface::Surface(SDL_Surface *surface)
{
    if (surface == nullptr) {
        throw "Surface is null";
    }
    _isLoaded = true;
    _surface = surface;
}

Surface::~Surface()
{
    if (_surface && _isLoaded) {
        SDL_FreeSurface(_surface);
    }
}

bool Surface::isLoaded() const
{
    return _isLoaded && _surface != NULL;
}

SDL_Surface *Surface::getSurface()
{
    return _surface;
}

void Surface::operator=(SDL_Surface *surface)
{
    if (_isLoaded && _surface != nullptr) {
        SDL_FreeSurface(_surface);
    }
    _surface = surface;
    _isLoaded = true;
}
