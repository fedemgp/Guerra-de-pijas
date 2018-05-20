//
// Created by Gorco on 19/05/18.
//

#ifndef INC_4_WORMS_STOPMOVE_H
#define INC_4_WORMS_STOPMOVE_H

#include <Box2D/Common/b2Math.h>
#include <vector>

#include "PlayerState.h"

namespace Worms {
class Still : public State {
   public:
    Still();
    ~Still() = default;
    const std::vector<float>& update(Player &p, float dt, float32 mass,
                                    const b2Vec2 &velocities) override;
    void moveRight(Player &p) override;
    void moveLeft(Player &p) override;
    void jump(Player &p) override;
    void stopMove(Player &p) override;
};
}

#endif  // INC_4_WORMS_STOPMOVE_H
