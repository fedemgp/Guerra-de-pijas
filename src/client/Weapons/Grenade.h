/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 04/06/18
 */

#ifndef __GRENADE_H__
#define __GRENADE_H__

#include <Camera.h>

#include "../GameTextures.h"
#include "Direction.h"
#include "PowerBar.h"
#include "Scope.h"
#include "Weapon.h"

#define GRENADE_CENTER_FRAME 15

namespace Worm {
class Grenade : public Weapon {
   public:
    explicit Grenade(const GUI::GameTextureManager &textureManager);
    ~Grenade() = default;
    void update(float dt) override;
    void render(GUI::Position &p, GUI::Camera &cam, SDL_RendererFlip &flip) override;
    void setAngle(float angle, Direction d) override;
    void startShot() override;
    void endShot() override;
    bool positionSelected() override;

   private:
    ::Weapon::Scope scope;
    ::Weapon::PowerBar powerBar;
};
}  // namespace Worm

#endif  //__GRENADE_H__
