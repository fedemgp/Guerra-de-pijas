//
// Created by rodrigo on 10/06/18.
//

#include <algorithm>

#include "StartTurn.h"

void Worms::StartTurn::endTurn(GameTurn &gt) {
    if (this->wormsFalling.size() == 0 && this->wormsDrowning.size() == 0 && !this->wormsDying && this->wormsDisconnectedDying.size() == 0) {
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

void Worms::StartTurn::wormDisconnectedDying(uint8_t wormId) {
    this->wormsDisconnectedDying.emplace_back(wormId);
    if (this->wormToFollow != this->wormsDisconnectedDying[0] && this->wormsFalling.size() == 0 && this->wormsDrowning.size() == 0) {
        this->wormToFollow = this->wormsDisconnectedDying[0];
        this->notify(*this, Event::NewWormToFollow);
    }
}

void Worms::StartTurn::wormDisconnectedDead(uint8_t wormId) {}
