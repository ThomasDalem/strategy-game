#ifndef SURFACE_HPP
#define SURFACE_HPP

#include <string>
#include <SDL2/SDL.h>

namespace SDL {
    class Surface {
    public:
        Surface(const std::string &filepath, SDL_Surface *winSurface = NULL);
        ~Surface();

        SDL_Surface *getSurface();
        bool isLoaded() const;

    private:
        SDL_Surface *_surface;
        bool _isLoaded;
    };
}

#endif // SURFACE_HPP