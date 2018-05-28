//
// Created by rodrigo on 28/05/18.
//

#ifndef INC_4_WORMS_NOWEAPONS_H
#define INC_4_WORMS_NOWEAPONS_H


#include "GameStateMsg.h"
#include "Worm.h"
#include "WormState.h"

namespace Worm {
    class NoWeapons : public State {
    public:
        NoWeapons();
        ~NoWeapons();
        virtual void update(float dt) override;
        virtual IO::PlayerInput moveRight(Worm &w) override;
        virtual IO::PlayerInput moveLeft(Worm &w) override;
        virtual IO::PlayerInput stopMove(Worm &w) override;
        virtual IO::PlayerInput jump(Worm &w) override;
        virtual IO::PlayerInput backFlip(Worm &w) override;
        virtual IO::PlayerInput bazooka(Worm &w) override;
        virtual IO::PlayerInput startShot(Worm &w) override;
        virtual IO::PlayerInput endShot(Worm &w) override;
        virtual IO::PlayerInput pointUp(Worm &w) override;
        virtual IO::PlayerInput pointDown(Worm &w) override;
    };
}  // namespace Worm

#endif //INC_4_WORMS_NOWEAPONS_H
