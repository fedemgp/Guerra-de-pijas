//
// Created by rodrigo on 10/06/18.
//

#include "GameClock.h"

GameClock::GameClock()
        : turnTime(Game::Config::getInstance().getTurnTime()),
          extraTurnTime(Game::Config::getInstance().getExtraTurnTime()),
          currentTurnTime(turnTime),
          waitForNextTurnTime(Game::Config::getInstance().getWaitForNextTurnTime()) {

}

void GameClock::playerShot() {
    this->currentTurnTime = this->extraTurnTime;
    this->timeElapsed = 0.0f;
}

void GameClock::update(float dt) {
    this->timeElapsed += dt;
    if (this->waitForNextTurn) {
        if (this->timeElapsed > this->waitForNextTurnTime) {
            this->timeElapsed = 0.0f;
            this->waitForNextTurn = false;
        }
    } else if (this->timeElapsed > this->currentTurnTime) {
            this->notify(*this, Event::EndTurn);
    }
}

double GameClock::getTimeElapsed() const {
    return this->timeElapsed;
}

double GameClock::getTurnTime() const {
    return this->currentTurnTime;
}

void GameClock::restart() {
    this->timeElapsed = 0.0f;
    this->currentTurnTime = this->turnTime;
//    this->waitForNextTurn = true;
}
