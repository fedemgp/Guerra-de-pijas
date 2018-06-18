//
// Created by rodrigo on 15/06/18.
//

#include <iostream>
#include "GamesGetter.h"
#include "Lobbies.h"

void Worms::Lobbies::createGame(int playerID) {
    std::lock_guard<std::mutex> lock(this->mutex);
    this->lobbies.emplace_back(playerID, this->idLobby);
    this->idLobby++;
}

void Worms::Lobbies::getGames(GamesGetter &getter) {
    std::lock_guard<std::mutex> lock(this->mutex);
    getter(this->lobbies);
}

void Worms::Lobbies::joinGame(int gameID, int playerID) {
    this->lobbies[gameID].join(playerID);
}
