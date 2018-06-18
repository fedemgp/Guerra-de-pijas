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
        id(id) {
    this->lobbyObservers.emplace_back(this);
    this->lobbyObservers.emplace_back(lobbyObs);
}

void Worms::GameLobbyAssistant::run() {
    try {
        std::cout<<"asdasdas\n";
        unsigned char command{COMMAND_GET_GAMES};
        while (command == COMMAND_GET_GAMES) {
            this->protocol >> command;
            std::cout << (int) command << std::endl;
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

}

void Worms::GameLobbyAssistant::createGame() {std::cout<<"adfsawrf"<<std::endl;
    this->lobbies.createGame(this->id, this->lobbyObservers);
}

void Worms::GameLobbyAssistant::getGames() {
    GamesGetter getter;std::cout<<"adfsawrf"<<std::endl;
    this->lobbies.getGames(getter);
    this->protocol << getter.lobbies;
//    for (std::string &str : getter.lobbies){
//        std::cout << str;
//    }
}

void Worms::GameLobbyAssistant::joinGame() {
    unsigned char gameID{0};
    this->protocol >> gameID;std::cout<<(int) gameID<<std::endl;
    this->lobbies.joinGame(gameID, this->id, this);
}

void Worms::GameLobbyAssistant::onNotify(Subject &subject, Event event) {
    switch (event) {
        case Event::NewPlayer: {
            auto &lobby = dynamic_cast<Lobby &>(subject);std::cout<<"notificacion "<<lobby.getActualPlayers()<<std::endl;
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