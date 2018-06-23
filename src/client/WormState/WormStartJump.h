/*
 *  Created by Rodrigo.
 *  date: 19/05/18
 */

#ifndef __WORM_START_JUMP_H__
#define __WORM_START_JUMP_H__

#include "../Worm.h"
#include "GameStateMsg.h"
#include "WormState.h"

namespace Worm {
class StartJump : public State {
   public:
    StartJump();
    ~StartJump();

    virtual void update(float dt) override;

    virtual IO::PlayerInput moveRight(Worm &w) override;
    virtual IO::PlayerInput moveLeft(Worm &w) override;
    virtual IO::PlayerInput stopMove(Worm &w) override;
    virtual IO::PlayerInput jump(Worm &w) override;
    virtual IO::PlayerInput setTimeoutTo(Worm &w, int t) override;

    virtual IO::PlayerInput bazooka(Worm &w) override;
    virtual IO::PlayerInput grenade(Worm &w) override;
    virtual IO::PlayerInput cluster(Worm &w) override;
    virtual IO::PlayerInput mortar(Worm &w) override;
    virtual IO::PlayerInput banana(Worm &w) override;
    virtual IO::PlayerInput holy(Worm &w) override;
    virtual IO::PlayerInput aerialAttack(Worm &w) override;
    virtual IO::PlayerInput dynamite(Worm &w) override;
    virtual IO::PlayerInput baseballBat(Worm &w) override;
    virtual IO::PlayerInput teleport(Worm &w) override;
    virtual IO::PlayerInput positionSelected(Worm &w) override;

    virtual IO::PlayerInput startShot(Worm &w) override;
    virtual IO::PlayerInput endShot(Worm &w) override;
    virtual IO::PlayerInput pointUp(Worm &w) override;
    virtual IO::PlayerInput pointDown(Worm &w) override;
    virtual IO::PlayerInput backFlip(Worm &w) override;
};
}  // namespace Worm

#endif  //__WORM_START_JUMP_H__
