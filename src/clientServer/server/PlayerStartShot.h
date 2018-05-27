//
// Created by rodrigo on 24/05/18.
//

#ifndef __PLAYER_STARTSHOT_H__
#define __PLAYER_STARTSHOT_H__


#include "PlayerState.h"

namespace Worms {
    class StartShot : public State {
    public:
        StartShot();
        ~StartShot() = default;
        void update(Player &p, float dt, b2Body *body) override;
        void moveRight(Player &p) override;
        void moveLeft(Player &p) override;
        void jump(Player &p) override;
        void bazooka(Player &p) override;
        void startShot(Player &p) override;
        void backFlip(Player &p) override;
        void stopMove(Player &p) override;
        void pointUp(Player &p) override;
        void pointDown(Player &p) override;
    };
}


#endif //__PLAYER_STARTSHOT_H__
