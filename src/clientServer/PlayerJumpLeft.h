//
// Created by Gorco on 19/05/18.
//

#ifndef INC_4_WORMS_JUMPLEFT_H
#define INC_4_WORMS_JUMPLEFT_H


#include "Player.h"

namespace Worms {
    class JumpLeft : public State {
        float update() override;
        void moveRight(Player &p) override;
        void moveLeft(Player &p) override;
        void jumpRight(Player &p) override;
        void jumpLeft(Player &p) override;
        void stopMove(Player &p) override;
    };
}


#endif //INC_4_WORMS_JUMPLEFT_H
