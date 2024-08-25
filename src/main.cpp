#include <iostream>
#include <SDL2/SDL.h>
#include "SDL/App.hpp"

#define SDL_MAIN_HANDLED // Error when compiling on windows if not set because of SDL_main

#include "utils/WinInfo.hpp"

#include "MainLoop.hpp"

int main()
{
    SDL::App app(1920, 1080);
    MainLoop mainLoop(app);

    WinInfo::getInstance().setApp(&app);

    mainLoop.loop();

    return (0);
}
