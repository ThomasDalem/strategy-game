#ifndef SHOP_HPP
#define SHOP_HPP

#include "entt.hpp"
#include "components/game/Unit.hpp"
#include "utils/TexturesLoader.hpp"

class Shop
{
public:
    Shop(entt::registry &reg, TexturesLoader &texturesLoader);
    ~Shop() = default;

    void buyUnit(UnitType type);

private:
    entt::registry &_reg;
    TexturesLoader &_texturesLoader;
};

#endif