//
// Created by rodrigo on 15/06/18.
//

#include <iostream>
#include "GamesGetter.h"
#include "Lobbies.h"

void Worms::Lobbies::createGame(int playerID, std::vector<Observer *> lobbyObservers, unsigned int levelSelected) {
    std::lock_guard<std::mutex> lock(this->mutex);
    this->lobbies.emplace_back(playerID, this->idLobby, lobbyObservers, this->levels[0/*levelSelected*/]);
    this->idLobby++;
}

void Worms::Lobbies::getGames(GamesGetter &getter) {
    std::lock_guard<std::mutex> lock(this->mutex);
    getter(this->lobbies);
}

void Worms::Lobbies::joinGame(int gameID, int playerID, Observer *lobbyObserver) {
    std::lock_guard<std::mutex> lock(this->mutex);
    auto it = this->lobbies.begin();
    while ((*it).getID() != gameID && it != this->lobbies.end()){
        it++;
    }
    (*it).addLobbyObserver(lobbyObserver);
    (*it).joinGame(playerID);
}

std::list<Worms::Lobby> &Worms::Lobbies::getLobbies() {
    return this->lobbies;
}

Worms::Lobbies::Lobbies(const std::vector<std::vector<std::string>> &levels) :
        levels(levels) {
}
