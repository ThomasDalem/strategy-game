#include "Draggable.hpp"

using namespace HUD;

Draggable::Draggable(const RectI &rect, DragSlots &slots, int currentSlot)
    : Interactable(rect.x, rect.y, rect.width, rect.height)
    , _isDragged(false)
    , _slots(slots)
    , _currentSlot(slots[currentSlot])
{}

ComponentType Draggable::getType() const
{
    return ComponentType::DRAGGABLE;
}

bool Draggable::isDragged() const
{
    return _isDragged;
}

void Draggable::onClickDown([[maybe_unused]]int x, [[maybe_unused]]int y)
{
    _isDragged = true;
    _isClicked = true;
}

void Draggable::onClick([[maybe_unused]]int x, [[maybe_unused]]int y)
{
    _rect.x = x;
    _rect.y = y;
}

void Draggable::onClickUp([[maybe_unused]]int x, [[maybe_unused]]int y)
{
    bool slotFound = false;

    for (auto &slot : _slots) {
        if (pointInRect(slot->getRect(), x, y)) {
            setPos(slot->getPos());
            _currentSlot = slot;
            slotFound = true;
            break;
        }
    }
    if (slotFound == false) {
        setPos(_currentSlot->getPos());
    }
    _isDragged = false;
    _isClicked = false;
}
