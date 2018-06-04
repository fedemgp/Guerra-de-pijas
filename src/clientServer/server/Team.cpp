//
// Created by rodrigo on 3/06/18.
//

#include "Team.h"

Worms::Team::Team(std::vector<uint8_t> &playerIDs)
        : playerIDs(std::move(playerIDs)) {}

void Worms::Team::checkAlive(std::vector<Player> &players) {
    if (this->alive) {
        bool teamAlive = false;
        for (auto teamPlayerID : this->playerIDs) {
            if (players[teamPlayerID].getStateId() != Worm::StateID::Dead) {
                teamAlive = true;
            }
        }
        if (!teamAlive) {
            this->alive = false;
        }
    }
}

bool Worms::Team::isAlive() {
    return this->alive;
}

uint8_t Worms::Team::getCurrentPlayerID() {
    return this->playerIDs[this->currentPlayer];
}

void Worms::Team::setCurrentPlayer(uint8_t currentPlayer) {
    this->currentPlayer = currentPlayer;
}

void Worms::Team::endTurn(std::vector<Worms::Player> &players) {
    do {
        this->currentPlayer = (this->currentPlayer + 1) % this->playerIDs.size();
    } while (players[this->getCurrentPlayerID()].getStateId() == Worm::StateID::Dead);
}
