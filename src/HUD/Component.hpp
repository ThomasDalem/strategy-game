#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include "utils/Vec.hpp"
#include "SDL/Renderer.hpp"

namespace HUD
{
    // Abstract class representing a UI component
    class Component
    {
    public:
        Component(int x = 0, int y = 0, int width = 0, int height = 0, bool hidden = false);
        virtual ~Component() = default;

        int getX() const;
        int getY() const;
        int getWidth() const;
        int getHeight() const;
        Vec2i getPos() const;
        const RectI &getRect() const;
        bool isHidden() const;

        void setX(int x);
        void setY(int y);
        void setWidth(int width);
        void setHeight(int height);
        void setPos(const Vec2i &pos);
        void setHidden(bool hidden);

        virtual void draw(SDL::Renderer &renderer) = 0;

    protected:
        RectI _rect;
        bool _hidden;
    };
}

#endif // COMPONENT_HPP