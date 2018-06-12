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

        void playerShot(Worm::WeaponID weaponID);
        void endTurn();
        void wormHit(uint8_t wormId);
        void explosion();
        void wormEndHit(uint8_t wormId);
        void wormDrowning(uint8_t wormId);
        void wormDrowned(uint8_t wormId);
        void restart();
        void update(float dt);

        void wormFalling(uint8_t wormId);

        void wormLanded(uint8_t wormId);

        void wormDead();

        void wormDying();

    private:
        std::shared_ptr<GameTurnState> state{nullptr};
        Observer &game;
        GameTurnStateID stateID;
        bool newState{false};
        uint8_t bulletFragments{1};
    };
}


#endif //INC_4_WORMS_GAMETURN_H
