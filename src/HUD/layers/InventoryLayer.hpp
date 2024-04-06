#ifndef INVENTORY_LAYER_HPP
#define INVENTORY_LAYER_HPP

#include "HUD/Layer.hpp"
#include "HUD/inventory/InventorySlot.hpp"
#include "utils/TexturesLoader.hpp"
#include "HUD/Draggable.hpp"

namespace HUD
{
    class InventoryLayer: public Layer
    {
    public:
        InventoryLayer(TexturesLoader &textureLoader, int screenWidth, int screenHeight);

        void handleInput(const SDL_Event &e, int mouseX, int mouseY);
        void checkMousePos(int x, int y);

    private:
        void clickedComponents(int x, int y);

        DragSlots _slots;
    };
}

#endif // INVENTORY_LAYER_HPP