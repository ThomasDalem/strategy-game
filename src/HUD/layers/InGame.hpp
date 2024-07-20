#ifndef INGAME_HPP
#define INGAME_HPP

#include "HUD/Layer.hpp"
#include "SDL/Renderer.hpp"
#include "utils/TexturesLoader.hpp"

namespace HUD
{
    class InGame : public Layer
    {
    public:
        InGame(SDL::Renderer &renderer, TexturesLoader &textureLoader);
        ~InGame() = default;

        virtual void handleInput([[maybe_unused]]const SDL_Event &e, [[maybe_unused]]int mouseX, [[maybe_unused]]int mouseY) {};
        virtual void checkMousePos([[maybe_unused]]int x, [[maybe_unused]]int y) {};
    };
}

#endif