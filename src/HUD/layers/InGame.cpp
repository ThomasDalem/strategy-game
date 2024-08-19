#include "HUD/layers/InGame.hpp"

#include <iostream>
#include <functional>

#include "HUD/DynamicText.hpp"
#include "HUD/Image.hpp"
#include "HUD/Box.hpp"
#include "HUD/game/BuyButton.hpp"

#include "game/Data.hpp"

using namespace HUD;

InGame::InGame(entt::registry &reg, SDL::Renderer &renderer, TexturesLoader &texturesLoader, uint16_t winW, uint16_t winH)
    : Layer()
    , _shop(reg, texturesLoader)
{
    _components.push_back(std::make_unique<Image>("../assets/bullets_icon.png", texturesLoader, 300, 20));
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
        const std::string imagePath("../assets/allied_infantry.png");
        auto f = std::bind(&Shop::buyUnit, _shop, UnitType::INFANTRY);
        _interactableComponents.push_back(std::make_shared<BuyButton>(posX, posY, 50, 50, imagePath, texturesLoader, 100, f));
    }
}
