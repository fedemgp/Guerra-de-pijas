//
// Created by rodrigo on 10/06/18.
//

#include "GameClock.h"

GameClock::GameClock()
    : turnTime(Game::Config::getInstance().getTurnTime()),
      extraTurnTime(Game::Config::getInstance().getExtraTurnTime()),
      currentTurnTime(turnTime),
      waitForNextTurnTime(Game::Config::getInstance().getWaitForNextTurnTime()) {}

void GameClock::playerShot() {
    this->currentTurnTime = this->extraTurnTime;
    this->timeElapsed = 0.0f;
}

void GameClock::update(float dt) {
    this->timeElapsed += dt;
    if (this->timeElapsed > this->currentTurnTime) {
        if (this->waitingForNextTurn) {
            this->notify(*this, Event::NextTurn);
        } else {
            this->notify(*this, Event::EndTurn);
        }
    }
}

double GameClock::getTimeElapsed() const {
    return this->timeElapsed;
}

double GameClock::getTurnTime() const {
    return this->currentTurnTime;
}

void GameClock::restart() {
    this->waitingForNextTurn = false;
    this->timeElapsed = 0.0f;
    this->currentTurnTime = this->turnTime;
}

void GameClock::endTurn() {
    this->timeElapsed = this->currentTurnTime + 1.0f;
    this->notify(*this, Event::EndTurn);
}

void GameClock::waitForNextTurn() {
    this->timeElapsed = 0.0f;
    this->currentTurnTime = this->waitForNextTurnTime;
    this->waitingForNextTurn = true;
}
