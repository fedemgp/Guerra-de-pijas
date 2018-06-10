/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 04/06/18
 */

#ifndef __Scope_H__
#define __Scope_H__

#include <Animation.h>
#include <Camera.h>
#include "Direction.h"
#include "GameTextures.h"

namespace Weapon {
class Scope {
   public:
    Scope(const GUI::GameTextureManager &tex);
    ~Scope() = default;
    void setAngle(float angle, Worm::Direction d);
    void update(float dt);
    void render(GUI::Position &p, GUI::Camera &cam, SDL_RendererFlip &flip);

   private:
    float angle{0.0f};
    GUI::Animation animation;
};
}

#endif  //__Scope_H__
