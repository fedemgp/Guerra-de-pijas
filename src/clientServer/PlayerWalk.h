#ifndef _PLAYERWALKLEFT_H
#define _PLAYERWALKLEFT_H

#include "PlayerState.h"

namespace Worms {
class Walk : public State {
   public:
    Walk();
    ~Walk() = default;
    void update(Player &p, float dt, b2Body *body) override;
    void moveRight(Player &p) override;
    void moveLeft(Player &p) override;
    void jump(Player &p) override;
    void backFlip(Player &p) override;
    void stopMove(Player &p) override;
};
}

#endif  //_PLAYERWALKLEFT_H
