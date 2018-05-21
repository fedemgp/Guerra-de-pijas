//
// Created by Gorco on 19/05/18.
//

#ifndef __WORMS_PLAYER_JUMP_RIGHT_H__
#define __WORMS_PLAYER_JUMP_RIGHT_H__

#include "Player.h"

#define JUMP_TIME 0.6f
#define JUMP_VEL_X 3.0f
#define JUMP_VEL_Y 6.0f

namespace Worms {
class StartJump : public State {
   public:
    StartJump();
    ~StartJump() = default;
    void update(Player &p, float dt, b2Body *body) override;
    void moveRight(Player &p) override;
    void moveLeft(Player &p) override;
    void jump(Player &p) override;
    void stopMove(Player &p) override;

   private:
    float timeElapsed{0.0f};
};
}// namespace Worms

#endif  // __WORMS_PLAYER_JUMP_RIGHT_H__
