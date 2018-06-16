/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 16/06/18
 */

#ifndef __AerialAttack_H__
#define __AerialAttack_H__

#define AERIAL_ATTACK_CENTER_FRAME 0

#include "Weapon.h"

namespace Worm {
class AerialAttack: public Weapon {
public:
    explicit AerialAttack(const GUI::GameTextureManager &textureManager);
    ~AerialAttack() = default;
    void update(float dt) override;
    void render(GUI::Position &p, GUI::Camera &cam, SDL_RendererFlip &flip) override;
    void setAngle(float angle, Direction d) override;
    void startShot() override;
    void endShot() override;
    bool positionSelected() override;

private:
    void endAnimation();

};
}  // namespace Worm


#endif //__AerialAttack_H__
