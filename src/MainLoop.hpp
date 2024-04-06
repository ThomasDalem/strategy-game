#ifndef MAINLOOP_HPP
#define MAINLOOP_HPP

#include "SDL2/SDL_image.h"
#include "SDL/App.hpp"

class MainLoop
{
public:
    MainLoop(SDL::App &app);
    ~MainLoop();

    void loop();

private:
    SDL::App &_app;
    bool _quit;
};

#endif // MAINLOOP_HPP