/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 04/06/18
 */

#ifndef __WEAPON_NONE_H__
#define __WEAPON_NONE_H__

#include <vector>

#include "Weapon.h"

namespace Worm {
class WeaponNone : public Weapon {
   public:
    explicit WeaponNone(const GUI::GameTextureManager &textureManager);
    ~WeaponNone() = default;
    void update(float dt) override;
    void render(GUI::Position &p, GUI::Camera &cam, SDL_RendererFlip &flip) override;
    void setAngle(float angle, Direction d) override;
    void startShot() override;
    void endShot() override;
    bool positionSelected() override;
};
}  // namespace Worm

#endif  //__WEAPON_NONE_H__
