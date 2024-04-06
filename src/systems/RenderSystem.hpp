#ifndef RENDERSYSTEM_HPP
#define RENDERSYSTEM_HPP

#include "entt.hpp"
#include "SDL/Renderer.hpp"

void updateRenderSystem(entt::registry &reg, SDL::Renderer &renderer, bool debug = false);

#endif // RENDERSYSTEM_HPP