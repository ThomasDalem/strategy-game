#ifndef MAINLOOP_HPP
#define MAINLOOP_HPP

#if defined(WIN32) || defined (_WIN32)
    #include "SDL_image.h"
#else
    #include "SDL2/SDL_image.h"
#endif

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