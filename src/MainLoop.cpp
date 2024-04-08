#include "entt.hpp"
#include "MainLoop.hpp"
#include "utils/TexturesLoader.hpp"
#include "utils/Timer.hpp"

#include "systems/RenderSystem.hpp"
#include "systems/AnimationSystem.hpp"
#include "systems/MovementSystem.hpp"
#include "systems/game/EnemySystem.hpp"
#include "systems/game/UnitSystem.hpp"

#include "entities/Units.hpp"

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

    makeAlliedInfantry(reg, texturesLoader, 500.0, 400.0);
    makeEnemyInfantry(reg, texturesLoader, 800.0, 600.0);
    makeBase(reg, texturesLoader, 500.0, 100.0);

    Timer frameTimer;
    Timer gameTimer;

    gameTimer.start();

    while (!_quit) {
        frameTimer.start();

        int mouseX = 0;
        int mouseY = 0;
        SDL_GetMouseState(&mouseX, &mouseY);

        dragUnits(reg);
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                _quit = true;
            }
            if (e.type == SDL_KEYDOWN) {
                handleInputs(reg, texturesLoader, e);
            }
        }

        _app.getRenderer().setDrawColor(50, 50, 50, 0);
        _app.getRenderer().clear();

        enemySystem(reg);
        shootEnemies(reg, gameTimer.getDeltaTime());
        moveSprites(reg, frameTimer.getDeltaTime());
        animateSprites(reg, gameTimer.getDeltaTime());
        updateRenderSystem(reg, _app.getRenderer(), true);

        _app.getRenderer().present();
    }
}
