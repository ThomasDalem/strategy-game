#ifndef INTERACTABLE_HPP
#define INTERACTABLE_HPP

#include "HUD/Component.hpp"

namespace HUD
{
    enum ComponentType
    {
        BUTTON,
        DRAGGABLE,
        SLOT,
        OTHER
    };

    class Interactable : public Component
    {
    public:
        Interactable(int x, int y, int width, int height);
        Interactable(const RectI &rect);

        virtual ComponentType getType() const = 0;

        virtual void onClickDown([[maybe_unused]]int x, [[maybe_unused]]int y) {};
        virtual void onClick([[maybe_unused]]int x, [[maybe_unused]]int y) {};
        virtual void onClickUp([[maybe_unused]]int x, [[maybe_unused]]int y) {};
        virtual void onHoverEnter() {};
        virtual void onHover() {};
        virtual void onHoverQuit() {};

        bool isHovered() const;
        bool isClicked() const;
    
    protected:
        bool _isHovered;
        bool _isClicked;
    };
}

#endif // INTERACTABLE_HPP
