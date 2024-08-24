#include <iostream>
#include <SDL2/SDL.h>
#include "SDL/App.hpp"

#define SDL_MAIN_HANDLED // Error when compiling on windows if not set because of SDL_main

#include "utils/Random.hpp"

#include "MainLoop.hpp"

int main()
{
    SDL::App app(1600, 900);
    MainLoop mainLoop(app);

    mainLoop.loop();

    return (0);
}
