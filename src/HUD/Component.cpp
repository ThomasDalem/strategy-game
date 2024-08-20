#include "Component.hpp"

using namespace HUD;

Component::Component(int x, int y, int width, int height, bool hidden)
    : _rect({x, y, width, height})
    , _hidden(hidden)
{}

Component::Component(const RectI &rect, bool hidden)
    : _rect(rect)
    , _hidden(hidden)
{}

int Component::getX() const
{
    return _rect.x;
}

int Component::getY() const
{
    return _rect.y;
}

int Component::getWidth() const
{
    return _rect.width;
}

int Component::getHeight() const
{
    return _rect.height;
}

Vec2i Component::getPos() const
{
    return {_rect.x, _rect.y};
}

const RectI &Component::getRect() const
{
    return _rect;
}

bool Component::isHidden() const
{
    return _hidden;
}

void Component::setX(int x)
{
    _rect.x = x;
}

void Component::setY(int y)
{
    _rect.y = y;
}

void Component::setWidth(int width)
{
    _rect.width = width;
}

void Component::setHeight(int height)
{
    _rect.height = height;
}

void Component::setPos(const Vec2i &pos)
{
    _rect.x = pos.x;
    _rect.y = pos.y;
}

void Component::setHidden(bool hidden)
{
    _hidden = hidden;
}
