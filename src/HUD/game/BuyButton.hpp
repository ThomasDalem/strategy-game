#ifndef BUY_BUTTON_HPP
#define BUY_BUTTON_HPP

#include <functional>

#include "HUD/Interactable.hpp"
#include "HUD/Image.hpp"
#include "HUD/Text.hpp"
#include "HUD/Box.hpp"
#include "components/game/Unit.hpp"
#include "utils/TexturesLoader.hpp"

namespace HUD
{
    class BuyButton : public Interactable
    {
    public:
        BuyButton(
            const RectI &rect,
            const std::string &imagePath,
            TexturesLoader &texturesLoader,
            SDL::Renderer &renderer,
            int price,
            std::function<void()> cb
        );
        ~BuyButton() = default;

        ComponentType getType() const override;
        void draw(SDL::Renderer &renderer) override;

        void onClickDown(int x, int y) override;
        inline void onHoverEnter() override;
        inline void onHoverQuit() override;

    private:
        std::function<void()> _callback;
        int _price;
        Image _image;
        Text _text;
        Box _box;
        bool _isHovered;
    };
}

#endif