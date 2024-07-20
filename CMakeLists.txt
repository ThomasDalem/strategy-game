cmake_minimum_required(VERSION 3.7)

project(game)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED On)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

set(SRCS
    src/HUD/Layer.cpp
    src/HUD/Component.cpp
    src/HUD/Interactable.cpp
    src/HUD/Draggable.cpp
    src/HUD/Image.cpp
    src/HUD/Button.cpp
    src/HUD/Text.cpp
    src/HUD/Font.cpp
    src/HUD/layers/InGame.cpp
    src/HUD/Box.cpp
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
    src/SDL/Font.cpp
    src/SDL/Text.cpp
    src/entities/Units.cpp
    src/entities/Bullet.cpp
    src/systems/RenderSystem.cpp
    src/systems/AnimationSystem.cpp
    src/systems/MovementSystem.cpp
    src/systems/CollisionSystem.cpp
    src/systems/game/EnemySystem.cpp
    src/systems/game/UnitSystem.cpp
    src/systems/game/BulletSystem.cpp
    src/game/Data.cpp
)

set(HEADERS
    src/HUD/Layer.hpp
    src/HUD/Component.hpp
    src/HUD/Interactable.hpp
    src/HUD/Draggable.hpp
    src/HUD/Image.hpp
    src/HUD/Button.hpp
    src/HUD/Text.hpp
    src/HUD/Font.hpp
    src/HUD/layers/InGame.hpp
    src/HUD/Box.hpp
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
    src/SDL/Font.hpp
    src/SDL/Text.hpp
    src/components/Position.hpp
    src/components/Sprite.hpp
    src/components/Animation.hpp
    src/components/Movement.hpp
    src/components/Relationship.hpp
    src/components/Collider.hpp
    src/components/Rectangle.hpp
    src/components/Circle.hpp
    src/components/Line.hpp
    src/components/game/Unit.hpp
    src/components/game/Allied.hpp
    src/components/game/Enemy.hpp
    src/components/game/BulletInfo.hpp
    src/components/game/Waypoint.hpp
    src/components/game/Selected.hpp
    src/components/tags/Base.hpp
    src/entities/Units.hpp
    src/entities/Bullet.hpp
    src/systems/RenderSystem.hpp
    src/systems/AnimationSystem.hpp
    src/systems/MovementSystem.hpp
    src/systems/CollisionSystem.hpp
    src/systems/game/EnemySystem.hpp
    src/systems/game/UnitSystem.hpp
    src/systems/game/BulletSystem.hpp
    src/game/Data.hpp
)

if (MSVC)
    # warning level 4
    add_compile_options(/W4)
else()
    # additional warnings
    add_compile_options(-Wall -Wextra -Wpedantic -g)
endif()

if (WIN32)
    set(PNG_LIBRARY "C:/Users/Thomas/vcpkg/packages/libpng_x64-windows/lib")
    set(PNG_PNG_INCLUDE_DIR "C:/Users/Thomas/vcpkg/packages/libpng_x64-windows/include")
    set(ZLIB_LIBRARY "C:/Users/Thomas/vcpkg/packages/zlib_x64-windows/lib")
    set(ZLIB_INCLUDE_DIR "C:/Users/Thomas/vcpkg/packages/zlib_x64-windows/include")
endif ()

if (WIN32)
    set(SDL2_image_DIR "C:/Users/Thomas/vcpkg/packages/sdl2-image_x64-windows/share/SDL2_image")
endif ()


if (WIN32)
    find_package(sdl2 CONFIG REQUIRED)
    find_package(SDL2_image CONFIG REQUIRED)
    find_package(sdl2-gfx CONFIG REQUIRED)
    find_package(sdl2-ttf CONFIG REQUIRED)
else ()
    find_package(SDL2 REQUIRED)
    find_package(SDL2_image REQUIRED)
    find_package(SDL2_gfx REQUIRED)
    find_package(SDL2_ttf REQUIRED)
endif ()

include_directories()

add_executable(game ${SRCS} ${HEADERS})

target_include_directories(game
    PUBLIC "src/"
    PUBLIC "include/"
    PUBLIC ${SDL2_INCLUDE_DIRS}
    PUBLIC ${SDL2_IMAGE_INCLUDE_DIRS}
    PUBLIC ${SDL2_GFX_INCLUDE_DIRS}
)

if (WIN32)
    target_link_libraries(game PUBLIC ${SDL2_LIBRARIES} SDL2::SDL2_image SDL2_gfx::SDL2_gfx SDL2::SDL2_ttf)
else ()
    target_link_libraries(game PUBLIC ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_GFX_LIBRARIES} ${SDL2_TTF_LIBRARIES})
endif ()