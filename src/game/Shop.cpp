#include "Shop.hpp"
#include "entities/Units.hpp"
#include "systems/game/UnitSystem.hpp"

Shop::Shop(entt::registry &reg, TexturesLoader &texturesLoader)
    : _reg(reg)
    , _texturesLoader(texturesLoader)
{}

void Shop::buyUnit(UnitType type)
{
    switch (type)
    {
    case UnitType::INFANTRY:
        createUnit(_reg, _texturesLoader, UnitType::INFANTRY);
        break;

    default:
        break;
    }
}
