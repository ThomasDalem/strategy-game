#include "entt.hpp"
#include "MainLoop.hpp"
#include "utils/TexturesLoader.hpp"
#include "utils/Timer.hpp"

#include "systems/RenderSystem.hpp"
#include "systems/AnimationSystem.hpp"
#include "systems/MovementSystem.hpp"
#include "systems/game/EnemySystem.hpp"
#include "systems/game/UnitSystem.hpp"
#include "systems/game/BulletSystem.hpp"

#include "entities/Units.hpp"

#include <iostream>

MainLoop::MainLoop(SDL::App &app): _app(app), _quit(false)
{

}

MainLoop::~MainLoop()
{

}

void MainLoop::loop()
{
    entt::registry reg;
    TexturesLoader texturesLoader(_app.getRenderer());
    SDL_Event e;

    const uint16_t screenCenterX = _app.getScreenWidth() / 2;
    const uint16_t screenCenterY = _app.getScreenHeight() / 2;
    makeBase(reg, texturesLoader, screenCenterX, screenCenterY);
    makeEnemyInfantry(reg, texturesLoader, 1000.f, 800.f);

    Timer frameTimer; // To calculate the time between frames
    Timer gameTimer;

    gameTimer.start();

    while (!_quit) {
        int mouseX = 0;
        int mouseY = 0;
        SDL_GetMouseState(&mouseX, &mouseY);

        dragUnits(reg);
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                _quit = true;
            }
            handleInputs(reg, texturesLoader, e);
        }

        _app.getRenderer().setDrawColor(50, 50, 50, 0);
        _app.getRenderer().clear();

        enemySystem(reg);
        spawnEnemies(reg, texturesLoader, gameTimer.getDeltaTime());
        makeEngagements(reg, gameTimer.getDeltaTime());
        checkUnitsHealth(reg);
        moveUnits(reg);
        moveObjects(reg, frameTimer.getDeltaTime());
        bulletSystem(reg, frameTimer.getDeltaTime());

        frameTimer.start();
        drawHealth(reg, _app.getRenderer());
        updateRenderSystem(reg, _app.getRenderer(), true);

        _app.getRenderer().present();
    }
}
