#ifndef BUY_BUTTON_HPP
#define BUY_BUTTON_HPP

#include <functional>

#include "HUD/Interactable.hpp"
#include "HUD/Image.hpp"
#include "components/game/Unit.hpp"
#include "utils/TexturesLoader.hpp"

namespace HUD
{
    class BuyButton : public Interactable, public Image
    {
    public:
        BuyButton(
            int x,
            int y,
            int width,
            int height,
            const std::string &imagePath,
            TexturesLoader &texturesLoader,
            int price,
            std::function<void()> cb
        );
        ~BuyButton() = default;

        ComponentType getType() const override;
        void draw(SDL::Renderer &renderer) override;

        void onClickDown(int x, int y) override;

    private:
        std::function<void()> _callback;
        int _price;
    };
}

#endif