#ifndef WIN_INFO_HPP
#define WIN_INFO_HPP

#include "SDL/App.hpp"
#include "utils/Vec.hpp"

class WinInfo
{
public:
    static WinInfo &getInstance()
    {
        static WinInfo info;
        return info;
    }

    WinInfo(const WinInfo &other) = delete;
    ~WinInfo() = default;

    Vec2i getScaledMousePos() const;
    Vec2i getMousePos() const;

    void setApp(SDL::App *app);
    void setMousePos(int x, int y);

    WinInfo &operator=(const WinInfo &other) = delete;

private:
    WinInfo();

    SDL::App *_app;
    Vec2i _mousePos;
};

#endif