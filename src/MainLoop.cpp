#include "entt.hpp"
#include "MainLoop.hpp"
#include "utils/TexturesLoader.hpp"
#include "utils/Timer.hpp"

#include "systems/RenderSystem.hpp"
#include "systems/AnimationSystem.hpp"
#include "systems/MovementSystem.hpp"
#include "systems/game/EnemyMovement.hpp"

#include "entities/Building.hpp"
#include "entities/Infantry.hpp"

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

    makeMachineGun(reg, texturesLoader, 300.0, 300.0);
    makeInfantry(reg, texturesLoader, 800.0, 600.0);
    makeBase(reg, texturesLoader, 500.0, 100.0);

    Timer frameTimer;
    Timer animTimer;

    animTimer.start();

    while (!_quit) {
        frameTimer.start();

        int mouseX = 0;
        int mouseY = 0;
        SDL_GetMouseState(&mouseX, &mouseY);

        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                _quit = true;
            }
        }

        _app.getRenderer().setDrawColor(50, 50, 50, 0);
        _app.getRenderer().clear();

        moveEnemies(reg);
        moveSprites(reg, frameTimer.getDeltaTime());
        animateSprites(reg, animTimer.getDeltaTime());
        updateRenderSystem(reg, _app.getRenderer(), true);

        _app.getRenderer().present();
    }
}
