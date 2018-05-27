/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 20/05/18
 */
#include "PlayerState.h"
#include "GameStateMsg.h"

Worms::State::State(Worm::StateID id) : stateID(id) {}

Worm::StateID Worms::State::getState() const {
    return this->stateID;
}
