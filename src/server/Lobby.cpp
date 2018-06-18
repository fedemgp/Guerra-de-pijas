//
// Created by rodrigo on 16/06/18.
//

#include <Stage.h>
#include <iostream>
#include "Lobby.h"
#include "Game.h"

Worms::Lobby::Lobby(int playerID, uint8_t id): id(id) {
    this->join(playerID);
}

void Worms::Lobby::join(int playerID) {
    this->playerIDs.emplace_back(playerID);
    this->actualPlayers++;
    this->notify(*this, Event::NewPlayer);
    if (this->actualPlayers == this->playersQuantity) {
        this->notify(*this, Event::StartGame);
    }
    this->startGame();
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

void Worms::Lobby::addPlayerSocket(CommunicationSocket &&player) {
//    this->players.push_back(player);
}

void Worms::Lobby::startGame() {
    std::cout << "game starts" << std::endl;
//    Worms::Game game{Worms::Stage{}, this->players};
}

Worms::Lobby::Lobby(Worms::Lobby &&other) : id(other.id){
    this->playersQuantity = other.playersQuantity;
    this->actualPlayers = other.actualPlayers;
    this->playerIDs = std::move(other.playerIDs);
    this->players = std::move(other.players);

}
