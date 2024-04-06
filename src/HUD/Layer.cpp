#include "Layer.hpp"

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
    if (_hidden) {
        return;
    }
    for (auto &component : _components) {
        if (component->isHidden()) {
            continue;
        }
        component->draw(renderer);
    }
    for (auto &component : _interactableComponents) {
        if (component->isHidden()) {
            continue;
        }
        component->draw(renderer);
    }
}
