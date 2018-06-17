//
// Created by rodrigo on 15/06/18.
//

#include <iostream>

#include "GameLobbyAssistant.h"
#include <GameStateMsg.h>
#include "Protocol.h"
#include "Lobbies.h"
#include "GamesGetter.h"

Worms::GameLobbyAssistant::GameLobbyAssistant(CommunicationSocket &&communicationSocket, Lobbies &lobbies, int id) :
        protocol(std::move(communicationSocket)),
        lobbies(lobbies),
        id(id) {
}

void Worms::GameLobbyAssistant::run() {
    try {
        std::cout<<"asdasdas\n";
//        unsigned char command;
//        this->protocol >> command;
//        switch (command) {
//            case COMMAND_CREATE_GAME:
//                this->createGame();
//                break;
//            case COMMAND_GET_GAMES:
//                this->getGames();
//                break;
//            case COMMAND_JOIN_GAME:
//                this->joinGame();
//                break;
//        }
        this->createGame();
        this->createGame();
        this->createGame();
        this->getGames();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unkown error in main thread" << std::endl;
    }
}

void Worms::GameLobbyAssistant::stop() {

}

void Worms::GameLobbyAssistant::createGame() {
    this->lobbies.createGame(this->id);
}

void Worms::GameLobbyAssistant::getGames() {
    GamesGetter getter;
    this->clearScreen();
    this->lobbies.getGames(getter);
    for (std::string &str : getter.lobbies){
        std::cout << str;
    }
}

void Worms::GameLobbyAssistant::joinGame() {

}

void Worms::GameLobbyAssistant::clearScreen(){
    std::cout << std::string(100, '\n');
}
