#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "HUD/Interactable.hpp"
#include "utils/Rect.hpp"

namespace HUD
{
    class Button : public Interactable
    {
    public:
        Button(int x, int y, int width, int height);

        ComponentType getType() const;
    };
}

#endif // BUTTON_HPP