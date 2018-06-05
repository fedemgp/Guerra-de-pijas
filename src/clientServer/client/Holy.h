/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 04/06/18
 */

#ifndef __HOLY_H__
#define __HOLY_H__


#include <vector>

#include "PowerBar.h"
#include "Scope.h"
#include "Weapon.h"

#define HOLY_CENTER_FRAME 15

namespace Worm{
    class Holy : public Weapon{
    public:
        explicit Holy(const GUI::GameTextureManager &textureManager);
        ~Holy() = default;
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


#endif //__HOLY_H__
