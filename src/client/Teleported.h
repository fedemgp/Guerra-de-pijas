//
// Created by rodrigo on 16/06/18.
//

#ifndef INC_4_WORMS_TELEPORTED_H
#define INC_4_WORMS_TELEPORTED_H


#include "WormState.h"

namespace Worm {
    class Teleported : public State {
    public:
        Teleported();
        ~Teleported();

        virtual void update(float dt) override;

        virtual IO::PlayerInput moveRight(Worm &w) override;
        virtual IO::PlayerInput moveLeft(Worm &w) override;
        virtual IO::PlayerInput stopMove(Worm &w) override;
        virtual IO::PlayerInput jump(Worm &w) override;
        virtual IO::PlayerInput backFlip(Worm &w) override;
        virtual IO::PlayerInput setTimeoutTo(Worm &w, int t) override;

        virtual IO::PlayerInput bazooka(Worm &w) override;
        virtual IO::PlayerInput grenade(Worm &w) override;
        virtual IO::PlayerInput cluster(Worm &w) override;
        virtual IO::PlayerInput mortar(Worm &w) override;
        virtual IO::PlayerInput banana(Worm &w) override;
        virtual IO::PlayerInput holy(Worm &w) override;
        virtual IO::PlayerInput aerialAttack(Worm &w) override;
        virtual IO::PlayerInput dynamite(Worm &w) override;
        virtual IO::PlayerInput teleport(Worm &w) override;
        virtual IO::PlayerInput positionSelected(Worm &w) override;

        virtual IO::PlayerInput startShot(Worm &w) override;
        virtual IO::PlayerInput endShot(Worm &w) override;
        virtual IO::PlayerInput pointUp(Worm &w) override;
        virtual IO::PlayerInput pointDown(Worm &w) override;
    };
}  // namespace Worm


#endif //INC_4_WORMS_TELEPORTED_H
