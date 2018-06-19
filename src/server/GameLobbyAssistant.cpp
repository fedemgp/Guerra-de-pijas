//
// Created by rodrigo on 15/06/18.
//

#include <iostream>

#include "GameLobbyAssistant.h"
#include <GameStateMsg.h>
#include "Protocol.h"
#include "Lobbies.h"
#include "GamesGetter.h"

Worms::GameLobbyAssistant::GameLobbyAssistant(CommunicationSocket &&communicationSocket, Lobbies &lobbies, int id,
                                              Observer *lobbyObs) :
        protocol(communicationSocket),
        lobbies(lobbies),
        playerID(id) {
    this->lobbyObservers.emplace_back(this);
    this->lobbyObservers.emplace_back(lobbyObs);
}

void Worms::GameLobbyAssistant::run() {
    try {
        std::uint8_t command{COMMAND_GET_GAMES};
        while (command == COMMAND_GET_GAMES) {
            this->protocol >> command;
            std::cout << "command: " << (int) command << std::endl;
            switch (command) {
                case COMMAND_CREATE_GAME:
                    this->createGame();
                    break;
                case COMMAND_GET_GAMES:
                    this->getGames();
                    break;
                case COMMAND_JOIN_GAME:
                    this->joinGame();
                    break;
            }
        }
//        this->createGame();
//        this->createGame();
//        this->createGame();
//        this->getGames();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unkown error in main thread" << std::endl;
    }
}

void Worms::GameLobbyAssistant::stop() {
    this->finished = true;
}

void Worms::GameLobbyAssistant::createGame() {
    this->lobbies.createGame(this->playerID, this->lobbyObservers);
}

void Worms::GameLobbyAssistant::getGames() {
    GamesGetter getter;
    this->lobbies.getGames(getter);
    this->protocol << getter.lobbies;
}

void Worms::GameLobbyAssistant::joinGame() {
    std::uint8_t gameID{0};
    this->protocol >> gameID;
    std::cout << "Joining game with ID " << (int) gameID << std::endl;
    this->lobbies.joinGame(gameID, this->playerID, this);
}

void Worms::GameLobbyAssistant::onNotify(Subject &subject, Event event) {
    switch (event) {
        case Event::NewPlayer: {
            auto &lobby = dynamic_cast<Lobby &>(subject);
            std::cout<<"new Player, actualPlayers: "<< (int) lobby.getActualPlayers()<<std::endl;
            this->protocol << lobby.getActualPlayers();
            break;
        }
        default: {
            break;
        }
    }
}

CommunicationSocket Worms::GameLobbyAssistant::getSocket() {
    return std::move(this->protocol.getSocket());
}

int Worms::GameLobbyAssistant::getPlayerID() const{
    return this->playerID;
}

bool Worms::GameLobbyAssistant::itsOver() const{
    return this->finished;
}
