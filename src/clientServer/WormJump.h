/*
 *  Created by Rodrigo.
 *  date: 19/05/18
 */

#ifndef __WORM_JUMP_H__
#define __WORM_JUMP_H__


#include "WormState.h"
#include "GameStateMsg.h"
#include "Worm.h"

namespace Worm {
class Jump : public State {
public:
    Jump();
    ~Jump();

    virtual void update(float dt) override;

    virtual IO::PlayerInput moveRight(Worm &w) override;
    virtual IO::PlayerInput moveLeft(Worm &w) override;
    virtual IO::PlayerInput stopMove(Worm &w) override;
    virtual IO::PlayerInput jump(Worm &w) override;
};
}  // namespace Worm


#endif //__WormJump_H__
