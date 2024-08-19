#include "BuyButton.hpp"

using namespace HUD;

BuyButton::BuyButton(
    int x,
    int y,
    int width,
    int height,
    const std::string &imagePath,
    TexturesLoader &texturesLoader,
    int price,
    std::function<void()> cb
) : Interactable(x, y, width, height)
  , Image(imagePath, texturesLoader, x, y)
  , _callback(cb)
  , _price(price)
{

}

ComponentType BuyButton::getType() const
{
    return ComponentType::BUTTON;
}

void BuyButton::draw(SDL::Renderer &renderer)
{
    Image::draw(renderer);
}

void BuyButton::onClickDown(int x, int y)
{
    _callback();
}
