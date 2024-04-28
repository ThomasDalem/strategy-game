#include <iostream>

#if defined(WIN32) || defined (_WIN32)
#include <SDL_image.h>
#else
#include "SDL2/SDL_image.h"
#endif

#include "Surface.hpp"

using namespace SDL;

Surface::Surface(const std::string &filepath, SDL_Surface *winSurface) : _isLoaded(false), _surface(nullptr)
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
