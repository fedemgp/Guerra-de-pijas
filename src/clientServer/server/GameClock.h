//
// Created by rodrigo on 10/06/18.
//

#ifndef INC_4_WORMS_GAMECLOCK_H
#define INC_4_WORMS_GAMECLOCK_H


#include "Config.h"
#include "Subject.h"

class GameClock : public Subject {
public:
    GameClock();
    ~GameClock() = default;
    void update(float dt);
    void playerShot();

    double getTimeElapsed() const;

    double getTurnTime() const;

    void restart();

    void endTurn();

private:
    float timeElapsed{0.0f};
    float turnTime;
    float extraTurnTime;
    float currentTurnTime;
    bool waitForNextTurn{false};
    float waitForNextTurnTime;
};


#endif //INC_4_WORMS_GAMECLOCK_H
