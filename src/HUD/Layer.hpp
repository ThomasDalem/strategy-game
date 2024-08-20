#ifndef LAYER_HPP
#define LAYER_HPP

#include <vector>
#include <unordered_map>
#include <memory>
#include "HUD/Component.hpp"
#include "HUD/Button.hpp"
#include "HUD/Interactable.hpp"
#include "SDL/Renderer.hpp"

namespace HUD
{
    class Layer
    {
    public:
        Layer(bool hidden = false);

        void setHidden(bool hidden);
        bool getHidden();

        void draw(SDL::Renderer &renderer);

        virtual void handleInput(const SDL_Event &e);
        virtual void checkMousePos(int x, int y) = 0;
    
    private:
        void checkHover(int x, int y);

    protected:
        std::vector<std::shared_ptr<Component>> _components;
        std::vector<std::shared_ptr<Interactable>> _interactableComponents;
        bool _hidden;
    };
}

#endif // LAYER_HPP