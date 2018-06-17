//
// Created by rodrigo on 16/06/18.
//

#include "Lobby.h"

Worms::Lobby::Lobby(int playerID, uint8_t id): id(id) {
    this->join(playerID);
}

void Worms::Lobby::join(int playerID) {
    this->playerIDs.emplace_back(playerID);
    this->actualPlayers++;
}

uint8_t Worms::Lobby::getPlayersQuantity() const{
    return this->playersQuantity;
}

uint8_t Worms::Lobby::getActualPlayers() const{
    return this->actualPlayers;
}

const std::vector<int> &Worms::Lobby::getPlayerIDs() const{
    return this->playerIDs;
}

uint8_t Worms::Lobby::getID() const{
    return this->id;
}
