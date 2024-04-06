#ifndef RECT_HPP
#define RECT_HPP

#include <ostream>

template<typename T>
struct Rect {
    T x;
    T y;
    T width;
    T height;

    operator SDL_Rect()
    {
        return {static_cast<int>(x), static_cast<int>(y), static_cast<int>(width), static_cast<int>(height)};
    }
};

template<typename T>
inline std::ostream &operator<< (std::ostream &os, const Rect<T> &rect)
{
    os << "x: " << rect.x
        << "\ty: " << rect.y
        << "\twidth: " << rect.width
        << "\theight: " << rect.height;
    return os;
}

template<typename T, typename P>
bool pointInRect(Rect<T> rect, P x, P y)
{
    return (x > rect.x && x < rect.x + rect.width) && (y > rect.y && y < rect.y + rect.height);
}

using RectI = Rect<int>;
using RectF = Rect<float>;
using RectD = Rect<double>;

#endif // RECT_HPP