#include "Button.hpp"

using namespace HUD;

Button::Button(int x, int y, int width, int height)
    : Interactable(x, y, width, height)
{}

ComponentType Button::getType() const
{
    return ComponentType::BUTTON;
}
