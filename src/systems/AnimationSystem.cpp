#include "AnimationSystem.hpp"
#include "components/Animation.hpp"
#include "components/Sprite.hpp"
#include <iostream>

void animateSprites(entt::registry &reg, uint64_t time)
{
    auto view = reg.view<Animation, Sprite>();

    view.each([time](Animation &anim, Sprite &sprite){
        if (anim.playAnim == false || anim.steps == 0) {
            return;
        }
        if (anim.curStep >= anim.steps - 1) {
            anim.curStep = 0;
            anim.startTime = time;
        }

        const uint64_t timePerFrame = anim.duration / static_cast<uint64_t>(anim.steps);
        const int currentStep = std::floor((time - anim.startTime) / timePerFrame);
        sprite.textureRect.x = anim.startPos.x + anim.spriteSize.x * currentStep;
        sprite.textureRect.y = anim.startPos.y;
        sprite.textureRect.height = anim.spriteSize.y;
        sprite.textureRect.width = anim.spriteSize.x;
        anim.curStep = currentStep;
    });
}
