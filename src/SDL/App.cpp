#include <iostream>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "App.hpp"

using namespace SDL;

App::App(uint16_t screenWidth, uint16_t screenHeight) : _screenWidth(screenWidth), _screenHeight(screenHeight)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        std::cout << "Error while initializing SDL : " << SDL_GetError() << std::endl;
        throw "Init error";
    }

    _window = SDL_CreateWindow(
        "Game",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        _screenWidth,
        _screenHeight,
        SDL_WINDOW_SHOWN
    );

    if (_window == NULL)
    {
        std::cout << "Error while creating the window : " << SDL_GetError() << std::endl;
        throw "Window error";
    }

    SDL_SetWindowResizable(_window, SDL_TRUE);

    _renderer.initRenderer(_window);

    _renderer.setDrawColor(50, 50, 50, 0);

    SDL_RenderSetLogicalSize(_renderer.getRenderer(), screenWidth, screenHeight);

    // Init PNG loading
    const int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        std::cout << "Error SDL_image could not initialize : " << IMG_GetError() << std::endl;
        throw "SDL_image error";
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        std::cout << "Error SDL_Mixer could not initialize : " << Mix_GetError() << std::endl;
        throw "SDL_mixer error";
    }
}

App::~App()
{
    SDL_DestroyWindow(_window);
    IMG_Quit();
    Mix_Quit();
    SDL_Quit();
}

SDL_Window *App::getWindow()
{
    return _window;
}

SDL_Surface *App::getSurface()
{
    return _surface;
}

Renderer &App::getRenderer()
{
    return _renderer;
}

uint16_t App::getScreenWidth() const noexcept
{
    return _screenWidth;
}

uint16_t App::getScreenHeight() const noexcept
{
    return _screenHeight;
}
