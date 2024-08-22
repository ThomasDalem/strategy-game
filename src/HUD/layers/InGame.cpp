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

    const int width = 100;
    const int height = 400;
    const int boxPosX = winW - width;
    const int boxPosY = winH / 2 - height / 2;
    _components.push_back(std::make_unique<Box>(RectI{boxPosX, boxPosY, width, height}, Color{255, 255, 255, 50}));

    {
        const int posX = boxPosX + 10;
        const int posY = boxPosY + 10;
        const std::string imagePath("../assets/allied_infantry.png");
        auto f = std::bind(&Shop::buyUnit, _shop, UnitType::INFANTRY);
        const RectI rect { posX, posY, 50, 50 };
        _interactableComponents.push_back(std::make_shared<BuyButton>(rect, imagePath, texturesLoader, renderer, 10, f));
    }
    {
        const std::shared_ptr<Interactable> &lastBtnPos = _interactableComponents.back();
        const int posX = boxPosX + 10;
        const int posY = lastBtnPos->getY() + lastBtnPos->getHeight() + 10;
        const std::string imagePath("../assets/armored.png");
        auto f = std::bind(&Shop::buyUnit, _shop, UnitType::ARMORED);
        const RectI rect { posX, posY, 50, 50 };
        _interactableComponents.push_back(std::make_shared<BuyButton>(rect, imagePath, texturesLoader, renderer, 100, f));
    }
}
