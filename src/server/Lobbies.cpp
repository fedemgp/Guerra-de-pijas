//
// Created by rodrigo on 15/06/18.
//

#include "Lobbies.h"

void Worms::Lobbies::createGame(int playerID) {
    this->lobbies.emplace_back(playerID);
}

const std::vector<Worms::Lobby> & Worms::Lobbies::getGames() {
    return this->lobbies;
}

void Worms::Lobbies::joinGame(int gameID, int playerID) {
    this->lobbies[gameID].join(playerID);
}
