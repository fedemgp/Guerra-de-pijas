//
// Created by rodrigo on 10/06/18.
//

#ifndef INC_4_WORMS_GAMETURNSTATE_H
#define INC_4_WORMS_GAMETURNSTATE_H


#include <cstdint>
#include "Subject.h"

namespace Worms {
    class GameTurn;
    class GameTurnState : public Subject {
    public:
        GameTurnState();
        virtual ~GameTurnState() = default;

        virtual void endTurn(GameTurn &gt) = 0;
        virtual void wormHit(GameTurn &gt, uint8_t wormId) = 0;
        virtual void wormEndHit(GameTurn &gt, uint8_t wormId) = 0;
        virtual void wormDrowning(GameTurn &gt, uint8_t wormId) = 0;
        virtual void wormDrowned(GameTurn &gt, uint8_t wormId) = 0;
    };
}


#endif //INC_4_WORMS_GAMETURNSTATE_H
