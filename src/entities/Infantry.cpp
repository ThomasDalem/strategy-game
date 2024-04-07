#include "Infantry.hpp"
#include "components/Sprite.hpp"
#include "components/Movement.hpp"
#include "components/game/Enemy.hpp"

entt::entity makeInfantry(entt::registry &reg, TexturesLoader &textureLoader, double x, double y)
{
    const entt::entity e = reg.create();

    reg.emplace<Sprite>(
        e,
        false,                   // Hidden
        Vec2d{x, y},             // Pos on screen
        Vec2f{1, 1},             // Scale
        RectI{-1, -1, -1, -1},   // Spritesheet rect
        RectD{x, y, 61.0, 61.0}, // Displayed sprite rect
        0.0,                     // Sprite angle
        SDL_FLIP_NONE,           // Texture flip
        textureLoader.getTexture("assets/infantry.png")
    );
    reg.emplace<Movement>(e, Vec2d{0.0, 0.0}, 1.0, false);
    reg.emplace<Enemy>(e, EnemyType::INFANTRY, 100);

    return e;
}
