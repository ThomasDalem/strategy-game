#ifndef DRAGGABLE_HPP
#define DRAGGABLE_HPP

#include <memory>
#include <vector>
#include "HUD/Interactable.hpp"

namespace HUD
{
    using DragSlots = std::vector<std::shared_ptr<Component>>;

    class Draggable : public Interactable
    {
    public:
        Draggable(const RectI &rect, DragSlots &slots, int currentSlot);

        ComponentType getType() const;

        bool isDragged() const;

        virtual void onClickDown(int x, int y);
        virtual void onClick(int x, int y);
        void onClickUp(int x, int y);
    
    protected:
        bool _isDragged;
        DragSlots &_slots;
        std::shared_ptr<Component> _currentSlot;
    };
}

#endif // DRAGGABLE_HPP