//
// Created by rodrigo on 10/06/18.
//

#include "PlayerShot.h"

void Worms::PlayerShot::endTurn(GameTurn &gt) {}

void Worms::PlayerShot::wormHit(GameTurn &gt, uint8_t wormId) {}

void Worms::PlayerShot::wormEndHit(Worms::GameTurn &gt, uint8_t wormId) {}

void Worms::PlayerShot::wormDrowning(Worms::GameTurn &gt, uint8_t wormId) {}

void Worms::PlayerShot::wormDrowned(Worms::GameTurn &gt, uint8_t wormId) {}

Worms::PlayerShot::PlayerShot() {}

void Worms::PlayerShot::explosion() {}

void Worms::PlayerShot::update(float dt) {}

void Worms::PlayerShot::wormDisconnectedDying(uint8_t wormId) {}

void Worms::PlayerShot::wormDisconnectedDead(uint8_t wormId) {}
