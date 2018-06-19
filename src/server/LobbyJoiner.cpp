//
// Created by rodrigo on 19/06/18.
//

#include "LobbyJoiner.h"

Worms::LobbyJoiner::LobbyJoiner(Worms::Lobbies &lobbies) :
        lobbies(lobbies.getLobbies()){
}

void Worms::LobbyJoiner::run() {
    while (!this->finished) {
        std::list<Lobby>::iterator lobbyIt;
        lobbyIt = this->lobbies.begin();
        while (lobbyIt != this->lobbies.end()){
            if (lobbyIt->itsOver()){
                lobbyIt->join();
                lobbyIt = this->lobbies.erase(lobbyIt);
            } else {
                lobbyIt++;
            }
        }
    }
}

void Worms::LobbyJoiner::stop() {
    this->finished = true;
}
