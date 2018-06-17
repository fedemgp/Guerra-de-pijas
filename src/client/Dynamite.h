/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 16/06/18
 */

#ifndef __DYNAMITE_H__
#define __DYNAMITE_H__

#include "Weapon.h"

#define DYNAMITE_CENTER_FRAME 0

namespace Worm{
class Dynamite: public Weapon {
public:
    explicit Dynamite(const GUI::GameTextureManager &textureManager);
    ~Dynamite() = default;
    void update(float dt) override;
    void render(GUI::Position &p, GUI::Camera &cam, SDL_RendererFlip &flip) override;
    void setAngle(float angle, Direction d) override;
    void startShot() override;
    void endShot() override;
    bool positionSelected() override;
};
}  // namespace Worm


#endif //__DYNAMITE_H__
