#include "Units.hpp"
#include "components/Position.hpp"
#include "components/Sprite.hpp"
#include "components/Movement.hpp"
#include "components/Circle.hpp"
#include "components/game/Enemy.hpp"
#include "components/game/Allied.hpp"
#include "components/game/Unit.hpp"
#include "components/tags/Base.hpp"

entt::entity makeBase(entt::registry &reg, TexturesLoader &textureLoader, float x, float y)
{
    const entt::entity e = reg.create();

    const UnitType unitType = UnitType::BASE;
    const int health = 100;
    const int ammo = 0;
    const int range = 0;
    const int damage = 0;
    const int fireRate = 0;
    const int speed = 0;
    const float lastShotTime = 0.f;
    const entt::entity target = entt::null;
    bool isActive = true;
    
    reg.emplace<Position>(e, x, y);
    reg.emplace<Unit>(e, unitType, health, ammo, range, damage, fireRate, speed, lastShotTime, target, isActive);
    Sprite &sprite = reg.emplace<Sprite>(
        e,
        false,                   // Hidden
        Vec2f{x, y},             // Pos on screen
        Vec2f{1.f, 1.f},         // Scale
        RectI{-1, -1, -1, -1},   // Spritesheet rect
        RectF{x, y, 61.f, 44.f}, // Displayed sprite rect
        0.f,                     // Sprite angle
        SDL_FLIP_NONE,           // Texture flip
        textureLoader.getTexture("../assets/base.png")
    );
    const Vec2i center = sprite.texture->getCenter();
    sprite.pos -= center;
    sprite.rect.x -= center.x;
    sprite.rect.y -= center.y;
    reg.emplace<Allied>(e, false);
    reg.emplace<Base>(e);

    return e;
}

entt::entity makeAlliedInfantry(entt::registry &reg, TexturesLoader &textureLoader, float x, float y)
{
    const entt::entity e = reg.create();

    const UnitType unitType = UnitType::INFANTRY;
    const int health = 100;
    const int ammo = 500;
    const int range = 200;
    const int damage = 10;
    const int fireRate = 10;
    const int speed = 50;
    const float lastShotTime = 0.f;
    const entt::entity target = entt::null;
    bool isActive = false;

    reg.emplace<Position>(e, x, y);
    reg.emplace<Unit>(e, unitType, health, ammo, range, damage, fireRate, speed, lastShotTime, target, isActive);
    const Sprite &sprite = reg.emplace<Sprite>(
        e,
        false,                   // Hidden
        Vec2f{x, y},             // Pos on screen
        Vec2f{1.f, 1.f},         // Scale
        RectI{-1, -1, -1, -1},   // Spritesheet rect
        RectF{x, y, 64.f, 64.f}, // Displayed sprite rect
        0.f,                     // Sprite angle
        SDL_FLIP_NONE,           // Texture flip
        textureLoader.getTexture("../assets/allied_infantry.png")
    );
    reg.emplace<Allied>(e, false);
    const Vec2i spriteCenter = sprite.texture->getCenter();
    reg.emplace<Circle>(e, Color{255, 255, 255, 255}, x + spriteCenter.x, y + spriteCenter.y, range, false, false);

    return e;
}

entt::entity makeEnemyInfantry(entt::registry &reg, TexturesLoader &textureLoader, float x, float y)
{
    const entt::entity e = reg.create();

    const UnitType unitType = UnitType::INFANTRY;
    const int health = 100;
    const int ammo = 500;
    const int range = 200;
    const int damage = 10;
    const int fireRate = 10;
    const int speed = 10;
    const float lastShotTime = 0.f;
    const entt::entity target = entt::null;
    bool isActive = true;

    reg.emplace<Position>(e, x, y);
    reg.emplace<Unit>(e, unitType, health, ammo, range, damage, fireRate, speed, lastShotTime, target, isActive);
    Sprite &sprite = reg.emplace<Sprite>(
        e,
        false,                   // Hidden
        Vec2f{x, y},             // Pos on screen
        Vec2f{1.f, 1.f},         // Scale
        RectI{-1, -1, -1, -1},   // Spritesheet rect
        RectF{x, y, 61.f, 61.f}, // Displayed sprite rect
        0.f,                     // Sprite angle
        SDL_FLIP_NONE,           // Texture flip
        textureLoader.getTexture("../assets/infantry.png")
    );
    const Vec2f center = sprite.texture->getCenter();
    sprite.pos -= center;
    sprite.rect.x -= center.x;
    sprite.rect.y -= center.y;
    reg.emplace<Movement>(e, Vec2f{0.f, 0.f}, 20.f, false);
    reg.emplace<Enemy>(e, UnitType::INFANTRY, 100);

    return e;
}
