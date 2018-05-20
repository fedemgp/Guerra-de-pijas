/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 20/05/18
 */

#ifndef __PLAYER_JUMPING_H__
#define __PLAYER_JUMPING_H__

#include "PlayerState.h"

namespace Worms{
class Jumping: public State{
public:
    Jumping();
    ~Jumping() = default;
    const std::vector<float>& update(Player &p, float dt, float32 mass,
                                     const b2Vec2 &velocities) override;
    void moveRight(Player &p) override;
    void moveLeft(Player &p) override;
    void jump(Player &p) override;
    void stopMove(Player &p) override;
};
}// namespace Worms

#endif //__PLAYER_JUMPING_H__
