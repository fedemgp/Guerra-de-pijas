//
// Created by rodrigo on 10/06/18.
//

#include "StartTurn.h"

void Worms::StartTurn::endTurn(GameTurn &gt) {
    this->notify(*this, Event::TurnEnded);
}

void Worms::StartTurn::wormHit(GameTurn &gt, uint8_t wormId) {

}

void Worms::StartTurn::wormEndHit(Worms::GameTurn &gt, uint8_t wormId) {

}

void Worms::StartTurn::wormDrowning(Worms::GameTurn &gt, uint8_t wormId) {

}

void Worms::StartTurn::wormDrowned(Worms::GameTurn &gt, uint8_t wormId) {

}

Worms::StartTurn::StartTurn() {

}
