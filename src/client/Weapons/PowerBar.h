/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 04/06/18
 */

#ifndef __PowerBar_H__
#define __PowerBar_H__

#include <Animation.h>
#include <Camera.h>
#include <vector>

#include "../GameTextures.h"
#include "Direction.h"

#define POWER_FRAMES_QUANTITY 16

namespace Weapon {
class PowerBar {
   public:
    explicit PowerBar(const GUI::GameTextureManager &tex);
    ~PowerBar() = default;
    void setAngle(float angle, Worm::Direction d);
    void update(float dt);
    void render(GUI::Position &p, GUI::Camera &cam, SDL_RendererFlip &flip);
    void startShot();
    void endShot();

   private:
    bool shotStarted{false};
    float angle{0.0f};
    float elapsedTime{0.0f};
    uint16_t power{0};
    std::vector<GUI::Animation> animations;
    const GUI::GameTextureManager &textureManager;
};
}

#endif  //__PowerBar_H__
