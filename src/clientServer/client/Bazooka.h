/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 04/06/18
 */

#ifndef __BAZOOKA_H__
#define __BAZOOKA_H__

#include <vector>

#include "PowerBar.h"
#include "Scope.h"
#include "Weapon.h"

#define BAZOOKA_CENTER_FRAME 16

namespace Worm{
    class Bazooka : public Weapon{
    public:
        explicit Bazooka(const GUI::GameTextureManager &textureManager);
        ~Bazooka() = default;
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


#endif //__BAZOOKA_H__
