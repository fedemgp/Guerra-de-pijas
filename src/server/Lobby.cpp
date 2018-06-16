//
// Created by rodrigo on 16/06/18.
//

#include "Lobby.h"

Worms::Lobby::Lobby(int playerID) {
    this->join(playerID);
}

void Worms::Lobby::join(int playerID) {
    this->playerIDs.emplace_back(playerID);
    this->actualPlayers++;
}
