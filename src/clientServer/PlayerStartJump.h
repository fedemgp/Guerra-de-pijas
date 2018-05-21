//
// Created by Gorco on 19/05/18.
//

#ifndef INC_4_WORMS_PLAYERJUMPRIGHT_H
#define INC_4_WORMS_PLAYERJUMPRIGHT_H

#include "Player.h"

#define JUMP_TIME 0.7f
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
}

#endif  // INC_4_WORMS_PLAYERJUMPRIGHT_H
