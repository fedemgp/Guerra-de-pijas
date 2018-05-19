#ifndef _PLAYERWALKRIGHT_H
#define _PLAYERWALKRIGHT_H


#include "PlayerState.h"

namespace Worms {
    class WalkRight : public State {
        float update() override;
        void moveRight(Player &p) override;
        void moveLeft(Player &p) override;
        void stopMove(Player &p) override;
    };
}


#endif //_PLAYERWALKRIGHT_H
