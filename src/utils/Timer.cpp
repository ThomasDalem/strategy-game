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
    _begin = SDL_GetTicks64();
}

uint64_t Timer::getDeltaTime() const
{
    return SDL_GetTicks64() - _begin;
}
