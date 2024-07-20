#include "HUD/layers/InGame.hpp"

#include "HUD/DynamicText.hpp"
#include "HUD/Image.hpp"
#include "HUD/Box.hpp"

#include "game/Data.hpp"

#include <iostream>

using namespace HUD;

InGame::InGame(SDL::Renderer &renderer, TexturesLoader &textureLoader, uint16_t winW, uint16_t winH) : Layer()
{
    _components.push_back(std::make_unique<Image>("../assets/bullets_icon.png", textureLoader, 300, 20));
    Vec2i iconPos = _components.back()->getPos();
    iconPos.x += _components.back()->getWidth() + 10;
    iconPos.y -= 10;
    _components.push_back(std::make_unique<DynamicText<int>>(&Data::getInstance().supplies, renderer, iconPos, 48));

    const float width = 100;
    const float height = 400;
    const float boxPosX = winW - width;
    const float boxPosY = winH / 2 - height / 2;
    _components.push_back(std::make_unique<Box>(RectF{boxPosX, boxPosY, width, height}, Color{255, 255, 255, 50}));
    
    {
        const int posX = boxPosX + 10;
        const int posY = boxPosY + 10;
        _components.push_back(std::make_unique<Image>("../assets/allied_infantry.png", textureLoader, posX, posY));
    }
}
