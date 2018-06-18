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
//    this->printCommands(commandInfo);
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

void Worm::LobbyAssistant::printCommands(std::vector<std::string> &vector){
    std::cout << "Select option" << std::endl;
    for (auto &string : vector){
        std::cout << string << std::endl;
    }
}
//TODO notify to the main thread that player select this so it can render properly
void Worm::LobbyAssistant::createGame(){
    this->protocol << this->command;
    while (this->playersQuantity < 2){
        this->protocol >> this->playersQuantity;
    }

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
    std::cin >> gameToJoin;
    this->protocol << gameToJoin;
}

CommunicationSocket &Worm::LobbyAssistant::getSocket() {
    return this->protocol.getSocket();
}


