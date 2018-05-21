/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 20/05/18
 */

#ifndef __PLAYER_END_JUMP_H__
#define __PLAYER_END_JUMP_H__

#include "PlayerState.h"

#define LAND_TIME 0.5f

namespace Worms{
    class EndJump: public State{
    public:
        EndJump();
        ~EndJump() = default;
        void update(Player &p, float dt, b2Body *body) override;
        void moveRight(Player &p) override;
        void moveLeft(Player &p) override;
        void jump(Player &p) override;
        void stopMove(Player &p) override;

    private:
        float timeElapsed{0.0f};
    };
}//namespace Worms


#endif //__PLAYER_END_JUMP_H__
