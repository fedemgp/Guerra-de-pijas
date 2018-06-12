//
// Created by rodrigo on 10/06/18.
//

#include <algorithm>
#include <iostream>

#include "GameStateMsg.h"
#include "ImpactOnCourse.h"

void Worms::ImpactOnCourse::endTurn(GameTurn &gt) {
    if (this->impactEnded && this->wormsFalling.size() == 0 && this->wormsDrowning.size() == 0 &&
        !this->wormsDying) {
        this->notify(*this, Event::TurnEnded);
    }
}

void Worms::ImpactOnCourse::wormHit(GameTurn &gt, uint8_t wormId) {
    this->wormsStillHit.emplace_back(wormId);
    this->wormsHit.emplace_back(wormId);
    if (this->wormToFollow != this->wormsStillHit[0]) {
        this->wormToFollow = this->wormsStillHit[0];
        this->notify(*this, Event::NewWormToFollow);
    }
}

void Worms::ImpactOnCourse::wormEndHit(Worms::GameTurn &gt, uint8_t wormId) {
    this->wormsStillHit.erase(
        std::remove(this->wormsStillHit.begin(), this->wormsStillHit.end(), wormId),
        this->wormsStillHit.end());
    if (this->wormToFollow == wormId) {
        this->wormToFollow = this->wormsStillHit[0];
        this->notify(*this, Event::NewWormToFollow);
    }
}

void Worms::ImpactOnCourse::wormDrowning(Worms::GameTurn &gt, uint8_t wormId) {
    this->wormsDrowning.emplace_back(wormId);
    this->wormLanded(wormId);
    if (this->wormsStillHit.size() == 0) {
        if (this->wormToFollow != this->wormsDrowning[0]) {
            this->wormToFollow = this->wormsDrowning[0];
            this->notify(*this, Event::NewWormToFollow);
        }
    }
}

void Worms::ImpactOnCourse::wormDrowned(Worms::GameTurn &gt, uint8_t wormId) {
    this->wormsDrowning.erase(
        std::remove(this->wormsDrowning.begin(), this->wormsDrowning.end(), wormId),
        this->wormsDrowning.end());
    if (this->wormsStillHit.size() == 0) {
        if (this->wormToFollow != this->wormsDrowning[0]) {
            this->wormToFollow = this->wormsDrowning[0];
            this->notify(*this, Event::NewWormToFollow);
        }
    }
}

uint8_t Worms::ImpactOnCourse::getWormToFollow() const {
    return this->wormToFollow;
}

std::vector<uint8_t> &Worms::ImpactOnCourse::getWormsHit() {
    return this->wormsHit;
}

void Worms::ImpactOnCourse::impactNotEnded() {
    this->impactEnded = false;
}

Worms::ImpactOnCourse::ImpactOnCourse(uint8_t bulletFragments) {
    this->bulletFragments = bulletFragments;
}

void Worms::ImpactOnCourse::explosion() {
    this->fragmentExplosions++;
}

void Worms::ImpactOnCourse::update(float dt) {
    if (!this->impactEnded) {
        if (this->wormsStillHit.size() == 0 && this->wormsDrowning.size() == 0 &&
            this->fragmentExplosions == this->bulletFragments) {
            this->impactEnded = true;
            this->notify(*this, Event::ImpactEnd);
        }
    }
}
