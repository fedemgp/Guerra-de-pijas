//
// Created by Gorco on 19/05/18.
//

#ifndef INC_4_WORMS_PLAYERJUMPRIGHT_H
#define INC_4_WORMS_PLAYERJUMPRIGHT_H

#include "Player.h"

namespace Worms {
class Jump : public State {
    float update(Player &p) override;
    void moveRight(Player &p) override;
    void moveLeft(Player &p) override;
    void jump(Player &p) override;
    void stopMove(Player &p) override;
};
}

#endif  // INC_4_WORMS_PLAYERJUMPRIGHT_H
