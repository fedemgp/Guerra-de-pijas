/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 04/06/18
 */

#ifndef __BANANA_H__
#define __BANANA_H__


#include <vector>

#include "PowerBar.h"
#include "Scope.h"
#include "Weapon.h"

#define BANANA_CENTER_FRAME 14

namespace Worm{
    class Banana : public Weapon{
    public:
        explicit Banana(const GUI::GameTextureManager &textureManager);
        ~Banana() = default;
        void update(float dt) override;
        void render(GUI::Position &p, GUI::Camera &cam, SDL_RendererFlip &flip) override;
        void setAngle(float angle, Direction d) override;
        void startShot() override;
        void endShot() override;

    private:
        ::Weapon::Scope scope;
        ::Weapon::PowerBar powerBar;
    };
} //namespace Worm


#endif //__BANANA_H__
