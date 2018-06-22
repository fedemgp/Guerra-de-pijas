//
// Created by rodrigo on 10/06/18.
//

#ifndef INC_4_WORMS_GAMECLOCK_H
#define INC_4_WORMS_GAMECLOCK_H

#include "Config/Config.h"
#include "Subject.h"

class GameClock : public Subject {
   public:
    GameClock();
    ~GameClock() = default;
    void update(float dt);
    void playerShot();
    double getTimeElapsed() const;
    double getTurnTime() const;
    void waitForNextTurn();
    void restart();
    void endTurn();

   private:
    float timeElapsed{0.0f};
    float turnTime;
    float extraTurnTime;
    float currentTurnTime;
    float waitForNextTurnTime;
    bool waitingForNextTurn{false};
};

#endif  // INC_4_WORMS_GAMECLOCK_H
