#include "HUD/Image.hpp"
#include "HUD/inventory/InventorySlot.hpp"
#include "HUD/inventory/InventoryItem.hpp"
#include "InventoryLayer.hpp"

using namespace HUD;

InventoryLayer::InventoryLayer(TexturesLoader &textureLoader, int screenWidth, int screenHeight): Layer()
{
    // Inventory image
    std::unique_ptr<Image> bagImage = std::make_unique<Image>("assets/bag.png", textureLoader);
    const int centerX = (screenWidth / 2) - (bagImage->getWidth() / 2);
    const int centerY = (screenHeight / 2) - (bagImage->getHeight() / 2);
    bagImage->setPos({centerX, centerY});

    const int bagTopPadding = 255;
    const int bagLeftPadding = 75;
    const int slotsPadding = 15;
    const int slotWidth = 60;
    const int slotHeight = 60;
    // Inventory slot
    const int inventoryRows = 6;
    const int inventoryCols = 5;
    for (int row = 0; row < inventoryRows; row++) {
        for (int col = 0; col < inventoryCols; col++) {
            const int posX = bagImage->getX() + bagLeftPadding + (slotWidth + slotsPadding) * col;
            const int posY = bagImage->getY() + bagTopPadding + (slotHeight + slotsPadding) * row;
            std::shared_ptr<InventorySlot> slot = std::make_shared<InventorySlot>(posX, posY, slotWidth, slotHeight);
            _interactableComponents.push_back(slot);
            _slots.push_back(slot);
        }
    }

    const int posX = bagImage->getX() + bagLeftPadding + (slotWidth + slotsPadding);
    const int posY = bagImage->getY() + bagTopPadding;
    const RectI slotRect { posX, posY, slotWidth, slotHeight };
    std::shared_ptr<InventoryItem> item
        = std::make_shared<InventoryItem>("assets/gun_item.png", textureLoader, slotRect, _slots, 0);
    _interactableComponents.push_back(std::move(item));

    _components.push_back(std::move(bagImage));
}

void InventoryLayer::handleInput(const SDL_Event &e, int mouseX, int mouseY)
{
    if (e.key.keysym.sym == SDLK_i) {
        _hidden = !_hidden;
    }
    if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
        for (auto &component : _interactableComponents) {
            if (pointInRect(component->getRect(), mouseX, mouseY)) {
                component->onClickDown(mouseX, mouseY);
            }
        }
    }
    if (e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT) {
        for (auto &component : _interactableComponents) {
            if (component->isClicked()) {
                component->onClickUp(mouseX, mouseY);
            }
        }
    }
}

void InventoryLayer::checkMousePos(int x, int y)
{
    for (auto &component : _interactableComponents) {
        if (pointInRect(component->getRect(), x, y)) {
            if (component->isHovered() == false) {
                component->onHoverEnter();
            }
            component->onHover(x, y);
        }
        else {
            if (component->isHovered() == true) {
                component->onHoverQuit();
            }
        }
    }
    clickedComponents(x, y);
}

void InventoryLayer::clickedComponents(int x, int y)
{
    for (auto &component : _interactableComponents) {
        if (component->isClicked()) {
            component->onClick(x, y);
        }
    }
}
