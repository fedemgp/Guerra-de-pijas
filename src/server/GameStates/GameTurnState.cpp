//
// Created by rodrigo on 10/06/18.
//

#include <algorithm>

#include "GameTurnState.h"

Worms::GameTurnState::GameTurnState() {}

void Worms::GameTurnState::wormFalling(uint8_t wormId) {
    this->wormsFalling.emplace_back(wormId);
}

void Worms::GameTurnState::wormLanded(uint8_t wormId) {
    this->wormsFalling.erase(
        std::remove(this->wormsFalling.begin(), this->wormsFalling.end(), wormId),
        this->wormsFalling.end());
}

void Worms::GameTurnState::wormDead() {
    this->wormsDying--;
}

void Worms::GameTurnState::wormDying() {
    this->wormsDying++;
}

uint8_t Worms::GameTurnState::getWormToFollow() const {
    return this->wormToFollow;
}
