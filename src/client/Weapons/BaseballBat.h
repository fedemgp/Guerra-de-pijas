//
// Created by rodrigo on 16/06/18.
//

#ifndef INC_4_WORMS_BASEBALLBAT_H
#define INC_4_WORMS_BASEBALLBAT_H

#include "Scope.h"
#include "Weapon.h"

#define BASEBALL_BAT_CENTER_FRAME 16

namespace Worm {
class BaseballBat : public Weapon {
   public:
    explicit BaseballBat(const GUI::GameTextureManager &textureManager);
    ~BaseballBat() = default;
    void update(float dt) override;
    void render(GUI::Position &p, GUI::Camera &cam, SDL_RendererFlip &flip) override;
    void setAngle(float angle, Direction d) override;
    void startShot() override;
    void endShot() override;
    bool positionSelected() override;

   private:
    ::Weapon::Scope scope;
};
}  // namespace Worm

#endif  // INC_4_WORMS_BASEBALLBAT_H
