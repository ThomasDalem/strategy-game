#include "Layer.hpp"

#include <iostream>

#include "utils/Rect.hpp"
#include "utils/WinInfo.hpp"

using namespace HUD;

Layer::Layer(bool hidden): _hidden(hidden)
{}

void Layer::setHidden(bool hidden)
{
    _hidden = hidden;
}

bool Layer::getHidden()
{
    return _hidden;
}

void Layer::draw(SDL::Renderer &renderer)
{
    if (_hidden)
    {
        return;
    }

    for (auto &component : _components)
    {
        if (component->isHidden())
        {
            continue;
        }
        component->draw(renderer);
    }
    for (auto &component : _interactableComponents)
    {
        if (component->isHidden())
        {
            continue;
        }
        component->draw(renderer);
    }
}

void Layer::handleInput(const SDL_Event &e)
{
    int x = 0;
    int y = 0;

    SDL_GetMouseState(&x, &y);
    Vec2i mousePos = WinInfo::getInstance().getScaledMousePos();

    if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
    {
        for (std::shared_ptr<Interactable> &component : _interactableComponents)
        {
            if (pointInRect(component->getRect(), mousePos.x, mousePos.y) == true)
            {
                component->onClickDown(mousePos.x, mousePos.y);
            }
        }
    }
    else if (e.type == SDL_MOUSEMOTION)
    {
        checkHover(mousePos.x, mousePos.y);
    }
}

void Layer::checkHover(int x, int y)
{
    for (std::shared_ptr<Interactable> &component : _interactableComponents)
    {
        //std::cout << component->getRect() << "\n";
        if (pointInRect(component->getRect(), x, y))
        {
            component->onHoverEnter();
        }
        else
        {
            component->onHoverQuit();
        }
    }
}
