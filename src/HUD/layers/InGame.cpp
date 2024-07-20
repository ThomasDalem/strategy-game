#include "HUD/layers/InGame.hpp"

#include "HUD/DynamicText.hpp"
#include "HUD/Image.hpp"

#include "game/Data.hpp"

#include <iostream>

using namespace HUD;

InGame::InGame(SDL::Renderer &renderer, TexturesLoader &textureLoader) : Layer()
{
    _components.push_back(std::make_unique<Image>("../assets/bullets_icon.png", textureLoader, 300, 20));
    std::cout << _components.back()->getWidth() << "\n";
    Vec2i iconPos = _components.back()->getPos();
    iconPos.x += _components.back()->getWidth() + 10;
    iconPos.y -= 10;
    _components.push_back(std::make_unique<DynamicText<int>>(&Data::getInstance().supplies, renderer, iconPos, 48));
}
