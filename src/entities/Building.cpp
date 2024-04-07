#include "Building.hpp"
#include "components/Sprite.hpp"
#include "components/Circle.hpp"
#include "components/game/BuildingInfo.hpp"
#include "components/tags/Base.hpp"

entt::entity makeMachineGun(entt::registry &reg, TexturesLoader &textureLoader, double x, double y)
{
    const entt::entity e = reg.create();

    const int health = 100;
    const int ammo = 500;
    const int range = 200;

    reg.emplace<BuildingInfo>(e, health, ammo, range);
    const Sprite &sprite = reg.emplace<Sprite>(
        e,
        false,                   // Hidden
        Vec2d{x, y},             // Pos on screen
        Vec2f{1, 1},             // Scale
        RectI{-1, -1, -1, -1},   // Spritesheet rect
        RectD{x, y, 64.0, 64.0}, // Displayed sprite rect
        0.0,                     // Sprite angle
        SDL_FLIP_NONE,           // Texture flip
        textureLoader.getTexture("assets/machine_gun.png")
    );
    const Vec2i spriteCenter = sprite.texture->getCenter();
    reg.emplace<Circle>(e, Color{255, 255, 255, 255}, x + spriteCenter.x, y + spriteCenter.y, range, false);

    return e;
}

entt::entity makeBase(entt::registry &reg, TexturesLoader &textureLoader, double x, double y)
{
    const entt::entity e = reg.create();

    const int health = 100;
    const int ammo = 0;
    const int range = 0;

    reg.emplace<BuildingInfo>(e, health, ammo, range);
    reg.emplace<Sprite>(
        e,
        false,                   // Hidden
        Vec2d{x, y},             // Pos on screen
        Vec2f{1, 1},             // Scale
        RectI{-1, -1, -1, -1},   // Spritesheet rect
        RectD{x, y, 61.0, 44.0}, // Displayed sprite rect
        0.0,                     // Sprite angle
        SDL_FLIP_NONE,           // Texture flip
        textureLoader.getTexture("assets/base.png")
    );
    reg.emplace<Base>(e);

    return e;
}
