#include <iostream>
#include "SDL/App.hpp"

#define SDL_MAIN_HANDLED // Error when compiling on windows if not set because of SDL_main
#include <SDL2/SDL.h>

#include "MainLoop.hpp"

int main()
{
    SDL::App app(1600, 900);
    MainLoop mainLoop(app);

    mainLoop.loop();

    return (0);
}
