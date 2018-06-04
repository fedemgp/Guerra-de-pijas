//
// Created by rodrigo on 3/06/18.
//

#ifndef INC_4_WORMS_FALLING_H
#define INC_4_WORMS_FALLING_H


#include "Player.h"

namespace Worms {
    class Falling : public State {
    public:
        Falling();
        ~Falling() = default;
        void update(Player &p, float dt, b2Body *body) override;
        void moveRight(Player &p) override;
        void moveLeft(Player &p) override;
        void jump(Player &p) override;
        void backFlip(Player &p) override;
        void stopMove(Player &p) override;

        void bazooka(Player &p) override;
        void grenade(Player &p) override;
        void cluster(Player &p) override;
        void mortar(Player &p) override;
        void banana(Player &p) override;
        void holy(Player &p) override;

        void startShot(Player &p) override;
        void endShot(Player &p) override;
        void pointUp(Player &p) override;
        void pointDown(Player &p) override;
    };
}  // namespace Worms


#endif //INC_4_WORMS_FALLING_H
