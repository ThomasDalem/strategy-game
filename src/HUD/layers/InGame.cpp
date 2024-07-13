#include "HUD/layers/InGame.hpp"

#include "HUD/Text.hpp"

using namespace HUD;

InGame::InGame(SDL::Renderer &renderer) : Layer()
{
    _components.push_back(std::make_unique<Text>("TEST", renderer, Vec2i{100, 100}, 52));
}
