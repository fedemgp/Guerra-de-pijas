/*
 *  Created by Rodrigo.
 *  date: 28/05/18
 */

#ifndef __Die_H__
#define __Die_H__

#include "WormState.h"

namespace Worm {
class Die : public State {
   public:
    Die();
    ~Die();

    virtual void update(float dt) override;

    virtual IO::PlayerInput moveRight(Worm &w) override;
    virtual IO::PlayerInput moveLeft(Worm &w) override;
    virtual IO::PlayerInput stopMove(Worm &w) override;
    virtual IO::PlayerInput jump(Worm &w) override;
    virtual IO::PlayerInput backFlip(Worm &w) override;
    virtual IO::PlayerInput bazooka(Worm &w) override;
    virtual IO::PlayerInput startShot(Worm &w) override;
    virtual IO::PlayerInput endShot(Worm &w) override;
    virtual IO::PlayerInput pointUp(Worm &w) override;
    virtual IO::PlayerInput pointDown(Worm &w) override;
};
}  // namespace Worm

#endif  //__Die_H__
