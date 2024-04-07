cmake_minimum_required(VERSION 3.7)

project(game)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

set(SRCS
    src/HUD/Layer.cpp
    src/HUD/Component.cpp
    src/HUD/Interactable.cpp
    src/HUD/Draggable.cpp
    src/HUD/Image.cpp
    src/HUD/Button.cpp
    src/main.cpp
    src/MainLoop.cpp
    src/utils/TexturesLoader.cpp
    src/utils/Timer.cpp
    src/utils/TransformUtils.cpp
    src/utils/Infos.cpp
    src/SDL/App.cpp
    src/SDL/Surface.cpp
    src/SDL/Texture.cpp
    src/SDL/Renderer.cpp
    src/entities/Units.cpp
    src/systems/RenderSystem.cpp
    src/systems/AnimationSystem.cpp
    src/systems/MovementSystem.cpp
    src/systems/CollisionSystem.cpp
    src/systems/game/EnemySystem.cpp
    src/systems/game/UnitSystem.cpp
)

set(HEADERS
    src/HUD/Layer.hpp
    src/HUD/Component.hpp
    src/HUD/Interactable.hpp
    src/HUD/Draggable.hpp
    src/HUD/Image.hpp
    src/HUD/Button.hpp
    src/MainLoop.hpp
    src/utils/Vec.hpp
    src/utils/Rect.hpp
    src/utils/TexturesLoader.hpp
    src/utils/Timer.hpp
    src/utils/TransformUtils.hpp
    src/utils/Infos.hpp
    src/utils/Color.hpp
    src/SDL/App.hpp
    src/SDL/Surface.hpp
    src/SDL/Texture.hpp
    src/SDL/Renderer.hpp
    src/components/Position.hpp
    src/components/Sprite.hpp
    src/components/Animation.hpp
    src/components/Movement.hpp
    src/components/Relationship.hpp
    src/components/Collider.hpp
    src/components/Rectangle.hpp
    src/components/Circle.hpp
    src/components/game/UnitInfo.hpp
    src/components/game/Unit.hpp
    src/components/tags/Base.hpp
    src/entities/Units.hpp
    src/systems/RenderSystem.hpp
    src/systems/AnimationSystem.hpp
    src/systems/MovementSystem.hpp
    src/systems/CollisionSystem.hpp
    src/systems/game/EnemySystem.hpp
    src/systems/game/UnitSystem.hpp
)

if (MSVC)
    # warning level 4
    add_compile_options(/W4)
else()
    # additional warnings
    add_compile_options(-Wall -Wextra -Wpedantic -g)
endif()

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_gfx REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_GFX_INCLUDE_DIRS})

add_executable(game ${SRCS} ${HEADERS})
target_include_directories(game PRIVATE "src/" "include/")
target_link_libraries(game ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_GFX_LIBRARIES})