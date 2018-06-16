//
// Created by rodrigo on 15/06/18.
//

#include <iostream>
#include "GameLobby.h"
#include "ServerSocket.h"
#include "Lobbies.h"

Worms::GameLobby::GameLobby(std::string port) :
        serverSocket(port.c_str()) {
    std::cout << "Se bindeo" << std::endl;
}

void Worms::GameLobby::start() {
    try {

        Lobbies lobbies{};
        int id = 0;

        while (!quit) {
            this->players.emplace_back(this->serverSocket.accept(), lobbies, id);
            this->players.back().start();
            id++;

            std::cout << "hubo una conexión" << std::endl;

//            auto it = players.begin();
//            while (it != players.end()) {
//                if (it->hasFinished()) {
//                    it->join();
//                    it = this->players.erase(it);
//                } else {
//                    it++;
//                }
//            }
        }
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unkown error in main thread" << std::endl;
    }
}

void Worms::GameLobby::exit() {
    this->quit = true;
}
