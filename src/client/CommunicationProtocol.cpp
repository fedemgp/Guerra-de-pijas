//
// Created by rodrigo on 20/06/18.
//

#include <iostream>
#include <GameStateMsg.h>
#include <Stream.h>
#include "CommunicationProtocol.h"

IO::CommunicationProtocol::CommunicationProtocol(ClientSocket &socket, IO::Stream<IO::ClientGUIMsg> *clientStream,
                                                 IO::Stream<IO::ServerResponse> *output) :
        protocol(socket),
        clientStream(clientStream),
        output(output) {
}

void IO::CommunicationProtocol::run() {
    while (!this->quit) {
        IO::ClientGUIMsg msg;
        if (clientStream->pop(msg)) {
            this->handleClientInput(msg);
        }
    }
    std::cout<<"dhsdfhs";
}

//void IO::CommunicationProtocol::clearScreen(){
//    std::cout << std::string(100, '\n');
//}

//void IO::CommunicationProtocol::printCommands() {
//    std::cout << "Select option" << std::endl;
//    std::cout << COMMAND_CREATE_GAME << " Create game." << std::endl
//              << COMMAND_JOIN_GAME << " Shows current lobbies. Must select one." << std::endl;
//}

//TODO notify to the main thread that player select this so it can render properly
void IO::CommunicationProtocol::createGame(){
    this->command = COMMAND_CREATE_GAME;
    this->protocol << this->command;
    this->waitGameStart();
}

void IO::CommunicationProtocol::getGames(){
    this->command = COMMAND_GET_GAMES;
    this->protocol << this->command;
    std::vector<std::uint8_t> games;
    this->protocol >> games;
//    this->clearScreen();
    std::cout << "Lobby ID\t\tIn room\t\t\tTotal players\n";
    std::uint8_t i{0};
    for (auto &uint : games){
        std::cout << (int) uint << "\t\t\t\t";
        if (i == 2) {
            std::cout << std::endl;
            i = 0;
        } else {
            i++;
        }
    }
    std::cout << std::endl;
}

void IO::CommunicationProtocol::joinGame(){
    this->getGames();
    std::uint8_t gameToJoin;
    std::cout<< "Choose lobby." << std::endl;
    std::cin >> gameToJoin;
    gameToJoin -= 48;
    this->command = COMMAND_JOIN_GAME;
    this->protocol << this->command;
    std::cout<<"mando sala "<< (int) gameToJoin<<std::endl;
    this->protocol << gameToJoin;
    this->waitGameStart();
}

ClientSocket IO::CommunicationProtocol::getSocket() {
    return std::move(this->protocol.getSocket());
}

void IO::CommunicationProtocol::waitGameStart() {
    while (this->playersQuantity < 2) {
        this->protocol >> this->playersQuantity;
        std::cout<< "players quantity " << (int) this->playersQuantity<<std::endl;
    } std::cout<<"Empieza\n";
    IO::ServerResponse sr{};
    sr.action = IO::ServerResponseAction::startGame;
    *this->output << sr;
}

void IO::CommunicationProtocol::stop() {
    this->quit = true;
}

void IO::CommunicationProtocol::handleClientInput(IO::ClientGUIMsg &msg) {
    switch (msg.input) {
        case IO::ClientGUIInput::createGame: {
            std::cout << " asdasd";
            this->createGame();
            break;
        }
        case IO::ClientGUIInput::joinGame: {
            std::cout << " asdasd";
            this->joinGame();
            break;
        }
        case IO::ClientGUIInput::quit: {
            std::cout << " asdasd";
            this->quit = true;
            break;
        }
        default: {
            break;
        }
    }
}
