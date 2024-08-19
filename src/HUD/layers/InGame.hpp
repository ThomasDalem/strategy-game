#ifndef INGAME_HPP
#define INGAME_HPP

#include "entt.hpp"
#include "HUD/Layer.hpp"
#include "SDL/Renderer.hpp"
#include "utils/TexturesLoader.hpp"
#include "game/Shop.hpp"

namespace HUD
{
    class InGame : public Layer
    {
    public:
        InGame(entt::registry &reg, SDL::Renderer &renderer, TexturesLoader &texturesLoader, uint16_t winW, uint16_t winH);
        ~InGame() = default;

        //virtual void handleInput([[maybe_unused]]const SDL_Event &e) {};
        virtual void checkMousePos([[maybe_unused]]int x, [[maybe_unused]]int y) {};

    private:
        Shop _shop;
    };
}

#endif