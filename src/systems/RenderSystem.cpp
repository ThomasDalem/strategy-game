#include "RenderSystem.hpp"
#include "components/Sprite.hpp"
#include "components/Collider.hpp"
#include "components/Rectangle.hpp"
#include "components/Circle.hpp"

void drawCollider(Collider &collider, SDL::Renderer &renderer)
{
    std::vector<SDL_FPoint> points;
    for (const Vec2d &vertex : collider.vertices) {
        SDL_FPoint point {static_cast<float>(vertex.x), static_cast<float>(vertex.y)};
        points.push_back(point);
    }
    // To make a line between the first and the last vertices
    SDL_FPoint point {
        static_cast<float>(collider.vertices[collider.vertices.size() - 1].x),
        static_cast<float>(collider.vertices[0].y)
    };
    points.push_back(point);

    renderer.setDrawColor(collider.drawColor.r, collider.drawColor.g, collider.drawColor.b, collider.drawColor.a);
    SDL_RenderDrawLinesF(renderer.getRenderer(), points.data(), collider.vertices.size() + 1);
    renderer.setDrawColor(50, 50, 50, 0);
}

void drawColliders(entt::registry &reg, SDL::Renderer &renderer)
{
    auto collidersView = reg.view<Collider>();
    collidersView.each([&](Collider &collider){
        drawCollider(collider, renderer);
    });
}

void drawCircles(entt::registry &reg, SDL::Renderer &renderer)
{
    auto view = reg.view<Circle>();
    view.each([&](Circle &circle){
        if (circle.hidden == false) {
            renderer.drawCircle(circle.x, circle.y, circle.radius, circle.color);
        }
    });
}

void updateRenderSystem(entt::registry &reg, SDL::Renderer &renderer, bool debug)
{
    const auto view = reg.view<Sprite>();

    auto f = [&](Sprite &sprite)
    {
        if (sprite.hidden) {
            return;
        }

        if (sprite.textureRect.height == -1) {
            sprite.rect.width = sprite.texture->getWidth() * sprite.scale.x;
            sprite.rect.height = sprite.texture->getHeight() * sprite.scale.y;
        }
        else {
            sprite.rect.width = sprite.textureRect.width * sprite.scale.x;
            sprite.rect.height = sprite.textureRect.height * sprite.scale.y;
        }

        SDL_Rect rect = {
            static_cast<int>(sprite.pos.x),
            static_cast<int>(sprite.pos.y),
            static_cast<int>(sprite.rect.width),
            static_cast<int>(sprite.rect.height)
        };

        if (sprite.textureRect.width < 0 || sprite.textureRect.height < 0) {
            renderer.copyEx(*sprite.texture.get(), sprite.angle, NULL, &rect, sprite.flip);
        }
        else {
            SDL_Rect spriteRect = {
                sprite.textureRect.x,
                sprite.textureRect.y,
                sprite.textureRect.width,
                sprite.textureRect.height
            };
            renderer.copyEx(*sprite.texture.get(), sprite.angle, &spriteRect, &rect, sprite.flip);
        }
    };
    view.each(f);
    drawCircles(reg, renderer);
    if (debug) {
        drawColliders(reg, renderer);
    }
}
