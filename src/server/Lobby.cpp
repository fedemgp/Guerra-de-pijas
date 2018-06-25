//
// Created by rodrigo on 16/06/18.
//

#include <iostream>
#include <string>

#include "Lobby.h"
#include "Stage.h"
#include "Game.h"


/** Copio por ¿posible race condition?
 */
Worms::Lobby::Lobby(int playerID, std::uint8_t id, std::vector<Observer *> obs, const IO::LevelData level,
                    const IO::LevelInfo levelInfo) :
        id(id),
        level(level),
        levelInfo(levelInfo) {
    for (auto *lobbyObserver : obs) {
        this->obs.emplace_back(lobbyObserver);
        this->addObserver(lobbyObserver);
    }
    this->joinGame(playerID);
}

void Worms::Lobby::joinGame(int playerID) {
//    std::lock_guard<std::mutex> lock(this->mutex);
    this->playerIDs.emplace_back(playerID);
    this->actualPlayers++;
    this->notify(*this, Event::NewPlayer);
    if (this->actualPlayers == levelInfo.playersQuantity) {
        this->notify(*this, Event::StartGame);
        std::uint8_t i{0};
        for (auto *obs : this->obs) {
            if (i != 0) {
                this->removeObserver(obs);
            }
            i++;
        }
        this->gameStarted = true;
    }
}

std::uint8_t Worms::Lobby::getPlayersQuantity() const{
    return this->levelInfo.playersQuantity;
}

std::uint8_t Worms::Lobby::getActualPlayers() const{
    return this->actualPlayers;
}

const std::vector<int> &Worms::Lobby::getPlayerIDs() const{
    return this->playerIDs;
}

std::uint8_t Worms::Lobby::getID() const{
    return this->id;
}

void Worms::Lobby::addPlayerSocket(CommunicationSocket &&player) {
    this->players.emplace_back(std::move(player));
}

Worms::Lobby::Lobby(Worms::Lobby &&other) noexcept :
        id(other.id),
        level(other.level),
        levelInfo(other.levelInfo) {
    if (this != &other){
        this->actualPlayers = other.actualPlayers;
        this->playerIDs = std::move(other.playerIDs);
        this->players = std::move(other.players);
    }
}

void Worms::Lobby::run() {
    while (!this->finished) {
        if (this->gameStarted) {
            for (std::uint8_t i = 0; i < levelInfo.playersQuantity; i++) {
                char buffer[1];
                buffer[0] = i;
                this->players[i].send(buffer, sizeof(buffer));
            }
            std::cout << "game starts" << std::endl;
            Worms::Game game{Worms::Stage::fromFile(this->level.levelPath), this->players};
            game.start();
            this->notify(*this, Event::EndGame);
            this->gameStarted = false;
            this->finished = true;
        }
    }
}

void Worms::Lobby::stop() {
    this->finished = true;
}

bool Worms::Lobby::itsOver() {
    return this->finished;
}

void Worms::Lobby::addLobbyObserver(Observer *lobbyObserver) {
    this->obs.emplace_back(lobbyObserver);
    this->addObserver(lobbyObserver);
}
