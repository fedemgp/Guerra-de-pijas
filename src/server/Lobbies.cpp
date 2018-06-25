//
// Created by rodrigo on 15/06/18.
//

#include <iostream>
#include <yaml-cpp/yaml.h>
#include "GamesGetter.h"
#include "Lobbies.h"

void Worms::Lobbies::createGame(int playerID, std::vector<Observer *> lobbyObservers, uint8_t levelSelected) {
    std::lock_guard<std::mutex> lock(this->mutex);
    this->lobbies.emplace_back(playerID, this->idLobby, lobbyObservers, this->levels[levelSelected], this->levelsInfo[levelSelected]);
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

Worms::Lobbies::Lobbies(const std::vector<IO::LevelData> &levels) :
        levels(levels) {
    for (auto &level : this->levels) {
        YAML::Node data = YAML::LoadFile(level.levelPath);
        std::string name = data["name"].as<std::string>();
        uint8_t playersQuantity = static_cast<uint8_t>(data["players"].as<int>());
        IO::LevelInfo levelInfo{name, playersQuantity};
        this->levelsInfo.emplace_back(levelInfo);
    }
}

const std::vector<IO::LevelInfo> &Worms::Lobbies::getLevels() {
    return this->levelsInfo;
}
