/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 20/05/18
 */

#ifndef __PLAYER_END_JUMP_H__
#define __PLAYER_END_JUMP_H__

#include "PlayerState.h"

namespace Worms {
class EndJump : public State {
   public:
    EndJump();
    ~EndJump() = default;
    void update(Player &p, float dt, b2Body *body) override;
    void moveRight(Player &p) override;
    void moveLeft(Player &p) override;
    void jump(Player &p) override;

    void bazooka(Player &p) override;
    void grenade(Player &p) override;
    void cluster(Player &p) override;

    void startShot(Player &p) override;
    void endShot(Player &p) override;
    void backFlip(Player &p) override;
    void stopMove(Player &p) override;
    virtual void pointUp(Player &p) override;
    virtual void pointDown(Player &p) override;

   private:
    float timeElapsed{0.0f};
    const float landTime;
};
}  // namespace Worms

#endif  //__PLAYER_END_JUMP_H__
