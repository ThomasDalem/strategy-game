#ifndef INGAME_HPP
#define INGAME_HPP

#include "HUD/Layer.hpp"
#include "SDL/Renderer.hpp"

namespace HUD
{
    class InGame : public Layer
    {
    public:
        InGame(SDL::Renderer &renderer);
        ~InGame() = default;

        virtual void handleInput(const SDL_Event &e, int mouseX, int mouseY) {};
        virtual void checkMousePos(int x, int y) {};
    };
}

#endif