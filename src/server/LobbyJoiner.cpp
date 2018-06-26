//
// Created by rodrigo on 19/06/18.
//

#include <GameStateMsg.h>
#include <iostream>
#include "LobbyJoiner.h"

Worms::LobbyJoiner::LobbyJoiner(Worms::Lobbies &lobbies, IO::Stream<IO::ServerInternalMsg> &serverInput) :
        lobbies(lobbies.getLobbies()),
        serverInput(serverInput) {
}

void Worms::LobbyJoiner::run() {
    try{
        while (!this->finished) {
            IO::ServerInternalMsg msg;
            if (this->serverInput.pop(msg)) {
                this->handleServerInput(msg);
            }
        }
    } catch (std::exception &e){
        if(!this->finished){
            std::cerr << "In LobbyJoiner::run()" << std::endl;
            std::cerr << e.what() << std::endl;
        }
    } catch (...){
        std::cerr << "Unknown error in LobbyJoiner::run()" << std::endl;
    }

    this->killLobbies();
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
            this->finished = true;
            break;
        }
    }
}

void Worms::LobbyJoiner::killLobbies(){
    for (auto &lobby: this->lobbies){
        if (lobby.started()) {
            lobby.stop();
            lobby.join();
        }
    }
    this->lobbies.erase(this->lobbies.begin(), this->lobbies.end());
}
