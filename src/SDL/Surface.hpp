#ifndef SURFACE_HPP
#define SURFACE_HPP

#include <string>
#include <SDL2/SDL.h>

namespace SDL {
    class Surface {
    public:
        Surface();
        Surface(const std::string &filepath, SDL_Surface *winSurface = NULL);
        Surface(SDL_Surface *surface);
        ~Surface();

        SDL_Surface *getSurface();
        bool isLoaded() const;

        void operator=(SDL_Surface *other);

    private:
        SDL_Surface *_surface;
        bool _isLoaded;
    };
}

#endif // SURFACE_HPP