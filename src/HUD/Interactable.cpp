#include "HUD/Interactable.hpp"

using namespace HUD;

Interactable::Interactable(int x, int y, int width, int height)
    : Component(x, y, width, height)
    , _isHovered(false)
    , _isClicked(false)
{}


Interactable::Interactable(const RectI &rect)
    : Component(rect)
    , _isHovered(false)
    , _isClicked(false)
{}

bool Interactable::isHovered() const
{
    return _isHovered;
}

bool Interactable::isClicked() const
{
    return _isClicked;
}
