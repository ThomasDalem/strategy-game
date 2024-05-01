#include "Timer.hpp"

Timer::Timer(): _begin(std::chrono::steady_clock::now())
{
}

Timer::~Timer()
{
}

void Timer::start()
{
    _begin = std::chrono::steady_clock::now();
}

float Timer::getDeltaTime() const
{
    const std::chrono::duration<float> fs = std::chrono::steady_clock::now() - _begin;
    return fs.count();
}
