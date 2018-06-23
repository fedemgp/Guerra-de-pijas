//
// Created by rodrigo on 10/06/18.
//

#include "GameTurn.h"
#include "Config/Config.h"
#include "GameStateMsg.h"
#include "GameStates/ImpactOnCourse.h"
#include "GameStates/PlayerShot.h"
#include "GameStates/StartTurn.h"

Worms::GameTurn::GameTurn(Observer &game) : game(game) {
    this->state = std::shared_ptr<GameTurnState>(new StartTurn());
    this->state->addObserver(&this->game);
}

void Worms::GameTurn::playerShot(Worm::WeaponID weaponID) {
    this->stateID = GameTurnStateID::PlayerShot;
    this->newState = true;

    switch (weaponID) {
        case Worm::WeaponID::WMortar:
            this->bulletFragments = ::Game::Config::getInstance().getMortarFragmentQuantity();
            break;
        case Worm::WeaponID::WCluster:
            this->bulletFragments = ::Game::Config::getInstance().getClusterFragmentQuantity();
            break;
        case Worm::WeaponID::WAerial:
            this->bulletFragments = ::Game::Config::getInstance().getAerialAttackMissileQuantity();
            break;
        default:
            break;
    }
}

void Worms::GameTurn::endTurn() {
    this->state->endTurn(*this);
}

void Worms::GameTurn::wormHit(uint8_t wormId) {
    this->state->wormHit(*this, wormId);
}

void Worms::GameTurn::explosion() {
    if (this->stateID != GameTurnStateID::ImpactOnCourse) {
        this->stateID = GameTurnStateID::ImpactOnCourse;
        this->state = std::shared_ptr<GameTurnState>(new ImpactOnCourse(this->bulletFragments));
        this->state->addObserver(&this->game);
    }
    this->state->explosion();
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
    this->bulletFragments = 1;
}

void Worms::GameTurn::update(float dt) {
    if (this->newState) {
        switch (this->stateID) {
            case GameTurnStateID::StartTurn:
                this->state = std::shared_ptr<GameTurnState>(new StartTurn());
                break;
            case GameTurnStateID::PlayerShot:
                this->state = std::shared_ptr<GameTurnState>(new PlayerShot());
                break;
            case GameTurnStateID::ImpactOnCourse:
                break;
        }
        this->state->addObserver(&this->game);
        this->newState = false;
    }
    this->state->update(dt);
}

void Worms::GameTurn::wormFalling(uint8_t wormId) {
    this->state->wormFalling(wormId);
}

void Worms::GameTurn::wormLanded(uint8_t wormId) {
    this->state->wormLanded(wormId);
}

void Worms::GameTurn::wormDead() {
    this->state->wormDead();
}

void Worms::GameTurn::wormDying() {
    this->state->wormDying();
}
