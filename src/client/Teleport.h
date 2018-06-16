//
// Created by rodrigo on 16/06/18.
//

#ifndef INC_4_WORMS_TELEPORT_H
#define INC_4_WORMS_TELEPORT_H


#define TELEPORT_CENTER_FRAME 0

#include "Weapon.h"

namespace Worm {
    class Teleport: public Weapon {
    public:
        explicit Teleport(const GUI::GameTextureManager &textureManager);
        ~Teleport() = default;
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


#endif //INC_4_WORMS_TELEPORT_H
