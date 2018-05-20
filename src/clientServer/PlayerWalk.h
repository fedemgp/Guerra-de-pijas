#ifndef _PLAYERWALKLEFT_H
#define _PLAYERWALKLEFT_H

#include "PlayerState.h"

namespace Worms {
class Walk : public State {
   public:
    Walk();
    ~Walk() = default;
    const std::vector<float>& update(Player &p, float dt, float32 mass,
                                    const b2Vec2 &velocities) override;
    void moveRight(Player &p) override;
    void moveLeft(Player &p) override;
    void jump(Player &p) override;

    void stopMove(Player &p) override;
};
}

#endif  //_PLAYERWALKLEFT_H
