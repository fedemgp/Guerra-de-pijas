/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 17/06/18
 */

#include <iostream>
#include <GameStateMsg.h>

#include "LobbyAssistant.h"

Worm::LobbyAssistant::LobbyAssistant(CommunicationSocket &socket):
        protocol(socket){}

void Worm::LobbyAssistant::run(){
//    std::vector<std::string> commandInfo;
//    this->protocol >> commandInfo;

    this->clearScreen();
    this->printCommands();
    std::cin >> this->command;
    this->command -= 48;
    switch(this->command){
        case COMMAND_CREATE_GAME: {
            this->createGame();
            break;
        }
        case COMMAND_JOIN_GAME: {
            this->joinGame();
            break;
        }
    }
}

void Worm::LobbyAssistant::clearScreen(){
    std::cout << std::string(100, '\n');
}

void Worm::LobbyAssistant::printCommands() {
    std::cout << "Select option" << std::endl;
    std::cout << COMMAND_CREATE_GAME << " Create game." << std::endl
              << COMMAND_JOIN_GAME << " Shows current lobbies. Must select one." << std::endl;
}
//TODO notify to the main thread that player select this so it can render properly
void Worm::LobbyAssistant::createGame(){
    this->protocol << this->command;
    this->waitGameStart();
}

void Worm::LobbyAssistant::getGames(){
    this->command = COMMAND_GET_GAMES;
    this->protocol << this->command;
    std::vector<std::uint8_t> games;
    this->protocol >> games;
//    this->clearScreen();
    std::cout << "Lobby ID\t\tPlayers in room\t\tTotal players\n";
    for (auto &uint : games){
        std::cout << (int) uint << "\t\t" << std::endl;
    }
}

void Worm::LobbyAssistant::joinGame(){
    this->getGames();
    unsigned char gameToJoin;
    std::cout<< "Choose lobby." << std::endl;
    std::cin >> gameToJoin;
    gameToJoin -= 48;
    this->command = COMMAND_JOIN_GAME;
    this->protocol << this->command;std::cout<<"mando sala "<<(int) gameToJoin<<std::endl;
    this->protocol << gameToJoin;
    this->waitGameStart();
}

CommunicationSocket Worm::LobbyAssistant::getSocket() {
    return std::move(this->protocol.getSocket());
}

void Worm::LobbyAssistant::waitGameStart() {
    while (this->playersQuantity < 2){
        this->protocol >> this->playersQuantity;std::cout<<(int)this->playersQuantity<<std::endl;
    }std::cout<<"Empieza\n";
}


