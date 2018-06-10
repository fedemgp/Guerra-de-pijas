//
// Created by rodrigo on 10/06/18.
//

#ifndef INC_4_WORMS_GAMETURN_H
#define INC_4_WORMS_GAMETURN_H


#include <memory>
#include "Subject.h"
#include "GameTurnState.h"

namespace Worms {
    enum class GameTurnStateID {
        StartTurn,
        PlayerShot,
        ImpactOnCourse
    };
    class Game;
    class GameTurn : public Subject {
    public:
        GameTurn(Observer &game);
        ~GameTurn() override = default;

        void playerShot();
        void endTurn();
        void wormHit(uint8_t wormId);
        void explosion();
        void wormEndHit(uint8_t wormId);
        void wormDrowning(uint8_t wormId);
        void wormDrowned(uint8_t wormId);
        void restart();
        void update(float dt);

    private:
        std::shared_ptr<GameTurnState> state{nullptr};
        Observer &game;
        GameTurnStateID stateID;
        bool newState{false};
    };
}


#endif //INC_4_WORMS_GAMETURN_H
