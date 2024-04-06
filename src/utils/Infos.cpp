#include "Infos.hpp"

#include "SDL2/SDL_filesystem.h"

Infos Infos::_infosInstance;

Infos::Infos()
{
    char *path = SDL_GetBasePath();
    _exePath = path;
    SDL_free(path);
}

Infos &Infos::getInstance() noexcept
{
    return _infosInstance;
}

const std::string &Infos::getExePath() const
{
    return _exePath;
}
