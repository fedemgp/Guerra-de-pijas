/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 20/05/18
 */

#ifndef __PLAYER_END_JUMP_H__
#define __PLAYER_END_JUMP_H__

#include "PlayerState.h"

#define JUMP_LAND_TIME 0.3f

namespace Worms{
    class EndJump: public State{
    public:
        EndJump();
        ~EndJump() = default;
        void update(Player &p, float dt, b2Body *body) override;
        void moveRight(Player &p) override;
        void moveLeft(Player &p) override;
        void jump(Player &p) override;
        void bazooka(Player &p) override;
        void startShot(Player &p) override;
        void backFlip(Player &p) override;
        void stopMove(Player &p) override;
        virtual void pointUp(Player &p) override;
        virtual void pointDown(Player &p) override;

    private:
        float timeElapsed{0.0f};
    };
}//namespace Worms


#endif //__PLAYER_END_JUMP_H__
