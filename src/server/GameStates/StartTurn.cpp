//
// Created by rodrigo on 10/06/18.
//

#include <algorithm>

#include "StartTurn.h"

void Worms::StartTurn::endTurn(GameTurn &gt) {
    if (this->wormsFalling.size() == 0 && this->wormsDrowning.size() == 0 && !this->wormsDying) {
        this->notify(*this, Event::TurnEnded);
    }
}

void Worms::StartTurn::wormHit(GameTurn &gt, uint8_t wormId) {}

void Worms::StartTurn::wormEndHit(Worms::GameTurn &gt, uint8_t wormId) {}

void Worms::StartTurn::wormDrowning(Worms::GameTurn &gt, uint8_t wormId) {
    this->wormsDrowning.emplace_back(wormId);
    this->wormLanded(wormId);
}

void Worms::StartTurn::wormDrowned(Worms::GameTurn &gt, uint8_t wormId) {
    this->wormsDrowning.erase(
        std::remove(this->wormsDrowning.begin(), this->wormsDrowning.end(), wormId),
        this->wormsDrowning.end());
}

Worms::StartTurn::StartTurn() {}

void Worms::StartTurn::explosion() {}

void Worms::StartTurn::update(float dt) {}
