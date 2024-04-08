#ifndef VEC_HPP
#define VEC_HPP

#include <SDL2/SDL_rect.h>
#include <ostream>

template<typename T>
struct Vec2 {
    T x;
    T y;

    Vec2<T>() = default;
    Vec2<T>(T aX, T aY): x(aX), y(aY) {}

    template<typename U>
    Vec2<T>(const Vec2<U> &other): x(static_cast<T>(other.x)), y(static_cast<T>(other.y)) {}

    Vec2<T> operator+(const Vec2<T> &other) const { return { x + other.x, y + other.y }; }
    Vec2<T> operator-(const Vec2<T> &other) const { return { x - other.x, y - other.y }; };
    Vec2<T> operator*(T m) const { return { x * m, y * m }; };

    Vec2<T> &operator+=(const Vec2<T> &other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }
    Vec2<T> &operator-=(const Vec2<T> &other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }
    Vec2<T> &operator*=(T m)
    {
        x *= m;
        y *= m;
        return *this;
    }

    bool operator==(const Vec2<T> &other) { return x == other.x && y == other.y; }
    bool operator!=(const Vec2<T> &other) { return x != other.x || y != other.y; }

    template<typename U>
    Vec2<T> &operator=(const Vec2<U> &other)
    {
        x = static_cast<T>(other.x);
        y = static_cast<T>(other.y);
        return *this;
    }

    operator SDL_Point() const { return { static_cast<int>(x), static_cast<int>(y) }; }
};

template<typename T>
inline std::ostream &operator<< (std::ostream &os, const Vec2<T> &v)
{
    os << "x: " << v.x << "\ty: " << v.y;
    return os;
}

using Vec2i = Vec2<int>;
using Vec2d = Vec2<double>;
using Vec2f = Vec2<float>;

template<typename T>
Vec2d normalize(const Vec2<T> &v)
{
    const double length = std::sqrt(v.x * v.x + v.y * v.y);
    return {v.x / length, v.y / length};
}

template<typename T>
double getDistance(const Vec2<T> &a, const Vec2<T> &b)
{
    return std::sqrt(std::pow(b.x - a.x, 2) + std::pow(b.y - a.y, 2));
}

#endif // VEC_HPP