//
// Created by rodrigo on 15/06/18.
//

#include <iostream>
#include <Stage.h>
#include "GameLobby.h"
#include "ServerSocket.h"
#include "Lobbies.h"
#include "Game.h"

Worms::GameLobby::GameLobby(std::string port) :
        serverSocket(port.c_str()) {
    std::cout << "Se bindeo" << std::endl;
}

void Worms::GameLobby::start() {
    try {

        Lobbies lobbies{};
        int id = 0;

        while (!quit) {
            this->players.emplace_back(this->serverSocket.accept(), lobbies, id, this);
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

void Worms::GameLobby::onNotify(Subject &subject, Event event) {
    switch (event) {
//        case Event::NewPlayer: {
//            auto lobby = dynamic_cast<const Lobby &>(subject);
//            const std::vector<int> &playerIDs = lobby.getPlayerIDs();
//            for (auto playerID : playerIDs) {
//                auto it = std::next(this->players.begin(), playerID);
//                (*it).newPlayer();
//            }
//            break;
//        }
        case Event::StartGame: {
            auto lobby = dynamic_cast<Lobby &>(subject);

            /** En algún momento le tengo que sacar el socket al GameLobbyAssistant
             *  para crear un vector con los sockets de todos los jugadores, que es lo que
             *  recibe Game, entonces pienso que es mejor que sea al momento de iniciar la partida
             *  por si el jugador se arrepiente antes y quiere salir, que el Assistant lo pueda
             *  manejar.
             */

            const std::vector<int> &playerIDs = lobby.getPlayerIDs();
            for (auto playerID : playerIDs) {
                auto it = std::next(this->players.begin(), playerID);
                lobby.addPlayerSocket(std::move((*it).getSocket()));
            }

            break;
        }
        default: {
            break;
        }
    }
}
