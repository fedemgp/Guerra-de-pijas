//
// Created by Gorco on 19/05/18.
//

#ifndef INC_4_WORMS_PLAYERJUMPRIGHT_H
#define INC_4_WORMS_PLAYERJUMPRIGHT_H

#include "Player.h"

#define JUMP_TIME 0.5f

#define JUMP_IMPULSE_Y 6.0f
#define JUMP_IMPULSE_X 1.0f

namespace Worms {
class StartJump : public State {
   public:
    StartJump();
    ~StartJump() = default;
    const std::vector<float>& update(Player &p, float dt, float32 mass,
                                      const b2Vec2 &velocities) override;
    void moveRight(Player &p) override;
    void moveLeft(Player &p) override;
    void jump(Player &p) override;
    void stopMove(Player &p) override;

   private:
    float timeElapsed{0.0f};
};
}

#endif  // INC_4_WORMS_PLAYERJUMPRIGHT_H
