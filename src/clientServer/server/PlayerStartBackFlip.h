/*
 *  Created by Rodrigo.
 *  date: 20/05/18
 */

#ifndef __PLAYER_START_BACK_FLIP_H__
#define __PLAYER_START_BACK_FLIP_H__

#include "Player.h"
#include "Config.h"

namespace Worms {
class StartBackFlip : public State {
   public:
    StartBackFlip();
    ~StartBackFlip() = default;
    void update(Player &p, float dt, b2Body *body) override;
    void moveRight(Player &p) override;
    void moveLeft(Player &p) override;
    void jump(Player &p) override;
    void backFlip(Player &p) override;
    void stopMove(Player &p) override;

    void bazooka(Player &p) override;
    void grenade(Player &p) override;
    void cluster(Player &p) override;

    void startShot(Player &p) override;
    void endShot(Player &p) override;
    void pointUp(Player &p) override;
    void pointDown(Player &p) override;

   private:
    float timeElapsed{0.0f};
    bool impulseApplied{false};
    const Math::Vector backflipVelocity;
    const float startJumpTime;
};
}

#endif  //__PLAYER_START_BACK_FLIP_H__
