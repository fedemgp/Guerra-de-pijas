//
// Created by rodrigo on 28/05/18.
//

#ifndef INC_4_WORMS_NOWEAPONS_H
#define INC_4_WORMS_NOWEAPONS_H


#include "PlayerState.h"

namespace Worms {
    class NoWeapons : public State {
    public:
        NoWeapons();
        ~NoWeapons() = default;
        void update(Player &p, float dt, b2Body *body) override;
        void moveRight(Player &p) override;
        void moveLeft(Player &p) override;
        void jump(Player &p) override;
        void backFlip(Player &p) override;
        void stopMove(Player &p) override;
        void bazooka(Player &p) override;
        void startShot(Player &p) override;
        void endShot(Player &p) override;
        void pointUp(Player &p) override;
        void pointDown(Player &p) override;
    };
}  // namespace Worms


#endif //INC_4_WORMS_NOWEAPONS_H