//
// Created by rodrigo on 10/06/18.
//

#include "GameTurn.h"
#include "PlayerShot.h"
#include "ImpactOnCourse.h"
#include "StartTurn.h"

Worms::GameTurn::GameTurn(Observer &game) : game(game) {
    this->state = std::shared_ptr<GameTurnState>(new StartTurn());
    this->state->addObserver(&this->game);
}

void Worms::GameTurn::playerShot() {
    this->stateID = GameTurnStateID::PlayerShot;
    this->newState = true;
}

void Worms::GameTurn::endTurn() {
    this->state->endTurn(*this);
}

void Worms::GameTurn::wormHit(uint8_t wormId) {
    this->state->wormHit(*this, wormId);
}

void Worms::GameTurn::explosion() {
    this->stateID = GameTurnStateID::ImpactOnCourse;
    this->state = std::shared_ptr<GameTurnState>(new ImpactOnCourse());
    this->state->addObserver(&this->game);
//    this->newState = true;
}

void Worms::GameTurn::wormEndHit(uint8_t wormId) {
    this->state->wormEndHit(*this, wormId);
}

void Worms::GameTurn::wormDrowning(uint8_t wormId) {
    this->state->wormDrowning(*this, wormId);
}

void Worms::GameTurn::wormDrowned(uint8_t wormId) {
    this->state->wormDrowned(*this, wormId);
}

void Worms::GameTurn::restart() {
    this->stateID = GameTurnStateID::StartTurn;
    this->newState = true;
}

void Worms::GameTurn::update(float dt) {
    if (this->newState) {
        switch(this->stateID) {
            case GameTurnStateID::StartTurn:
                this->state = std::shared_ptr<GameTurnState>(new StartTurn());
                break;
            case GameTurnStateID::PlayerShot:
                this->state = std::shared_ptr<GameTurnState>(new PlayerShot());
                break;
            case GameTurnStateID::ImpactOnCourse:
                this->state = std::shared_ptr<GameTurnState>(new ImpactOnCourse());
                break;
        }
        this->state->addObserver(&this->game);
        this->newState = false;
    }
}
