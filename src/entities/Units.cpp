#include "Units.hpp"
#include "components/Position.hpp"
#include "components/Sprite.hpp"
#include "components/Movement.hpp"
#include "components/Circle.hpp"
#include "components/game/Enemy.hpp"
#include "components/game/Allied.hpp"
#include "components/game/Unit.hpp"
#include "components/tags/Base.hpp"
#include "components/Sound.hpp"
#include "utils/SoundLoader.hpp"

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
    const bool isHidden = false;
    const std::uint8_t alpha = SDL_ALPHA_OPAQUE;
    
    reg.emplace<Position>(e, x, y);
    reg.emplace<Unit>(e, unitType, health, health, ammo, range, range, damage, fireRate, speed, speed, lastShotTime, target, isHidden);
    Sprite &sprite = reg.emplace<Sprite>(
        e,
        false,                   // Hidden
        Vec2f{x, y},             // Pos on screen
        Vec2f{1.f, 1.f},         // Scale
        RectI{-1, -1, -1, -1},   // Spritesheet rect
        RectF{x, y, 61.f, 44.f}, // Displayed sprite rect
        0.f,                     // Sprite angle
        SDL_FLIP_NONE,           // Texture flip
        textureLoader.getTexture("../assets/base.png"),
        alpha
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
    const bool isHidden = false;
    const std::uint8_t alpha = SDL_ALPHA_OPAQUE;

    reg.emplace<Position>(e, x, y);
    reg.emplace<Unit>(e, unitType, health, health, ammo, range, range, damage, fireRate, speed, speed, lastShotTime, target, isHidden);
    Sprite &sprite = reg.emplace<Sprite>(
        e,
        false,                   // Hidden
        Vec2f{x, y},             // Pos on screen
        Vec2f{1.f, 1.f},         // Scale
        RectI{-1, -1, -1, -1},   // Spritesheet rect
        RectF{x, y, 64.f, 64.f}, // Displayed sprite rect
        0.f,                     // Sprite angle
        SDL_FLIP_NONE,           // Texture flip
        textureLoader.getTexture("../assets/allied_infantry.png"),
        alpha
    );
    const bool isDragged = false;
    reg.emplace<Allied>(e, isDragged);
    const Vec2i spriteCenter = sprite.texture->getCenter();
    sprite.pos -= spriteCenter;
    reg.emplace<Circle>(e, Color{255, 255, 255, 255}, x, y, range, false, true);

    return e;
}

entt::entity makeFriendlyArmored(entt::registry &reg, TexturesLoader &textureLoader, float x, float y)
{
    const entt::entity e = reg.create();

    const UnitType unitType = UnitType::ARMORED;
    const int health = 500;
    const int ammo = 500;
    const int range = 300;
    const int damage = 50;
    const int fireRate = 30;
    const int speed = 30;
    const float lastShotTime = 0.f;
    const entt::entity target = entt::null;
    const bool isHidden = false;
    const std::uint8_t alpha = SDL_ALPHA_OPAQUE;

    reg.emplace<Position>(e, x, y);
    reg.emplace<Unit>(e, unitType, health, health, ammo, range, range, damage, fireRate, speed, speed, lastShotTime, target, isHidden);
    Sprite &sprite = reg.emplace<Sprite>(
        e,
        false,                   // Hidden
        Vec2f{x, y},             // Pos on screen
        Vec2f{1.f, 1.f},         // Scale
        RectI{-1, -1, -1, -1},   // Spritesheet rect
        RectF{x, y, 64.f, 64.f}, // Displayed sprite rect
        0.f,                     // Sprite angle
        SDL_FLIP_NONE,           // Texture flip
        textureLoader.getTexture("../assets/armored.png"),
        alpha
    );
    const bool isDragged = false;
    reg.emplace<Allied>(e, isDragged);
    const Vec2i spriteCenter = sprite.texture->getCenter();
    sprite.pos -= spriteCenter;
    reg.emplace<Circle>(e, Color{255, 255, 255, 255}, x, y, range, false, true);

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
    const bool isHidden = false;
    const std::uint8_t alpha = SDL_ALPHA_OPAQUE;

    reg.emplace<Position>(e, x, y);
    reg.emplace<Unit>(e, unitType, health, health, ammo, range, range, damage, fireRate, speed, speed, lastShotTime, target, isHidden);
    Sprite &sprite = reg.emplace<Sprite>(
        e,
        false,                   // Hidden
        Vec2f{x, y},             // Pos on screen
        Vec2f{1.f, 1.f},         // Scale
        RectI{-1, -1, -1, -1},   // Spritesheet rect
        RectF{x, y, 61.f, 61.f}, // Displayed sprite rect
        0.f,                     // Sprite angle
        SDL_FLIP_NONE,           // Texture flip
        textureLoader.getTexture("../assets/infantry.png"),
        alpha
    );
    const Vec2f center = sprite.texture->getCenter();
    sprite.pos -= center;
    sprite.rect.x -= center.x;
    sprite.rect.y -= center.y;
    reg.emplace<Movement>(e, Vec2f{0.f, 0.f}, 20.f, false);
    reg.emplace<Enemy>(e, UnitType::INFANTRY, 100);

    return e;
}

entt::entity makeHostileArmored(entt::registry &reg, TexturesLoader &textureLoader, float x, float y)
{
    const entt::entity e = reg.create();

    const UnitType unitType = UnitType::ARMORED;
    const int health = 500;
    const int ammo = 500;
    const int range = 300;
    const int damage = 50;
    const int fireRate = 30;
    const int speed = 30;
    const float lastShotTime = 0.f;
    const entt::entity target = entt::null;
    const bool isHidden = false;
    const std::uint8_t alpha = SDL_ALPHA_OPAQUE;

    reg.emplace<Position>(e, x, y);
    reg.emplace<Unit>(e, unitType, health, health, ammo, range, range, damage, fireRate, speed, speed, lastShotTime, target, isHidden);
    Sprite &sprite = reg.emplace<Sprite>(
        e,
        false,                   // Hidden
        Vec2f{x, y},             // Pos on screen
        Vec2f{1.f, 1.f},         // Scale
        RectI{-1, -1, -1, -1},   // Spritesheet rect
        RectF{x, y, 62.f, 62.f}, // Displayed sprite rect
        0.f,                     // Sprite angle
        SDL_FLIP_NONE,           // Texture flip
        textureLoader.getTexture("../assets/hostile_armored.png"),
        alpha
    );
    const Vec2f center = sprite.texture->getCenter();
    sprite.pos -= center;
    sprite.rect.x -= center.x;
    sprite.rect.y -= center.y;
    reg.emplace<Movement>(e, Vec2f{0.f, 0.f}, 20.f, false);
    reg.emplace<Enemy>(e, UnitType::ARMORED, 100);

    return e;
}
