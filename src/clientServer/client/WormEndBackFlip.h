/*
 *  Created by Rodrigo.
 *  date: 21/05/18
 */

#ifndef __WORM_END_BACKFLIP_H__
#define __WORM_END_BACKFLIP_H__

#include "GameStateMsg.h"
#include "WormState.h"

namespace Worm {
class EndBackFlip : public State {
   public:
    EndBackFlip();
    ~EndBackFlip();

    virtual void update(float dt) override;

    virtual IO::PlayerInput moveRight(Worm &w) override;
    virtual IO::PlayerInput moveLeft(Worm &w) override;
    virtual IO::PlayerInput stopMove(Worm &w) override;
    virtual IO::PlayerInput jump(Worm &w) override;
    virtual IO::PlayerInput backFlip(Worm &w) override;

    virtual IO::PlayerInput bazooka(Worm &w) override;
    virtual IO::PlayerInput grenade(Worm &w) override;
    virtual IO::PlayerInput cluster(Worm &w) override;
    virtual IO::PlayerInput mortar(Worm &w) override;
    virtual IO::PlayerInput banana(Worm &w) override;

    virtual IO::PlayerInput endShot(Worm &w) override;
    virtual IO::PlayerInput startShot(Worm &w) override;
    virtual IO::PlayerInput pointUp(Worm &w) override;
    virtual IO::PlayerInput pointDown(Worm &w) override;
};
}  // namespace Worm

#endif  //__WORM_END_BACKFLIP_H__
