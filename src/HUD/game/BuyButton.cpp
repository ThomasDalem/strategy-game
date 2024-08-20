#include "BuyButton.hpp"

using namespace HUD;

BuyButton::BuyButton(
    const RectI &rect,
    const std::string &imagePath,
    TexturesLoader &texturesLoader,
    SDL::Renderer &renderer,
    int price,
    std::function<void()> cb
) : Interactable(rect)
  , _callback(cb)
  , _price(price)
  , _image(imagePath, texturesLoader, rect.x, rect.y)
  , _text(std::to_string(price), renderer, {rect.x, rect.y}, 36)
  , _box(rect, {100, 100, 100, 150})
{
    _box.setWidth(_image.getWidth());
    _box.setHeight(_image.getHeight());
    _rect = _image.getRect();
    //_text.setPos(_text.getPos() + _image.getCenter()); // TODO: center text on image 
}

ComponentType BuyButton::getType() const
{
    return ComponentType::BUTTON;
}

void BuyButton::draw(SDL::Renderer &renderer)
{
    _image.draw(renderer);
    if (_isHovered)
    {
        _box.draw(renderer);
        _text.draw(renderer);
    }
}

void BuyButton::onClickDown(int x, int y)
{
    _callback();
}

void BuyButton::onHoverEnter()
{
    _isHovered = true;
}

void BuyButton::onHoverQuit()
{
    _isHovered = false;
}
