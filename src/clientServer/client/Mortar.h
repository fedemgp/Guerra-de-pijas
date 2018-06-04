/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 04/06/18
 */

#ifndef __MORTAR_H__
#define __MORTAR_H__


#include <vector>

#include "PowerBar.h"
#include "Scope.h"
#include "Weapon.h"

#define MORTAR_CENTER_FRAME 16

namespace Worm{
    class Mortar : public Weapon{
    public:
        explicit Mortar(const GUI::GameTextureManager &textureManager);
        ~Mortar() = default;
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


#endif //__MORTAR_H__
