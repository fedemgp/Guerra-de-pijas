//
// Created by rodrigo on 19/06/18.
//

#include <GameStateMsg.h>
#include "LobbyJoiner.h"

Worms::LobbyJoiner::LobbyJoiner(Worms::Lobbies &lobbies, IO::Stream<IO::ServerInternalMsg> &serverInput) :
        lobbies(lobbies.getLobbies()),
        serverInput(serverInput) {
}

void Worms::LobbyJoiner::run() {
    while (!this->finished) {
        IO::ServerInternalMsg msg;
        if (this->serverInput.pop(msg)) {
            this->handleServerInput(msg);
        }
    }
}

void Worms::LobbyJoiner::stop() {
    this->finished = true;
}

void Worms::LobbyJoiner::handleServerInput(IO::ServerInternalMsg &msg) {
    switch (msg.action) {
        case IO::ServerInternalAction::lobbyFinished: {
            std::list<Lobby>::iterator lobbyIt;
            lobbyIt = this->lobbies.begin();
            while (lobbyIt != this->lobbies.end()) {
                if (lobbyIt->itsOver()) {
                    lobbyIt->join();
                    lobbyIt = this->lobbies.erase(lobbyIt);
                } else {
                    lobbyIt++;
                }
            }
            break;
        }
        case IO::ServerInternalAction::quit: {
            this->killLobbies();
            this->finished = true;
            break;
        }
    }
}

void Worms::LobbyJoiner::killLobbies(){
    for (auto &lobby: this->lobbies){
        lobby.stop();
        lobby.join();
    }
    this->lobbies.erase(this->lobbies.begin(), this->lobbies.end());
}
