#include <SDL2/SDL.h>
#include "Timer.hpp"

Timer::Timer()
{
}

Timer::~Timer()
{
}

void Timer::start()
{
    _begin = SDL_GetTicks();
}

uint32_t Timer::getDeltaTime() const
{
    return SDL_GetTicks() - _begin;
}
