//
// Created by rodrigo on 15/06/18.
//

#include <iostream>
#include "GamesGetter.h"
#include "Lobbies.h"

void Worms::Lobbies::createGame(int playerID, std::vector<Observer *> lobbyObservers) {
    std::lock_guard<std::mutex> lock(this->mutex);
    this->lobbies.emplace_back(playerID, this->idLobby);
    this->lobbies.back().start();
    for (auto *lobbyObserver : lobbyObservers) {
        this->lobbies.back().addObserver(lobbyObserver);
    }
    this->idLobby++;
}

void Worms::Lobbies::getGames(GamesGetter &getter) {
    std::lock_guard<std::mutex> lock(this->mutex);
    getter(this->lobbies);
}

void Worms::Lobbies::joinGame(int gameID, int playerID, Observer *lobbyObserver) {
    std::lock_guard<std::mutex> lock(this->mutex);
    this->lobbies[gameID].addObserver(lobbyObserver);
    this->lobbies[gameID].joinGame(playerID);
}
