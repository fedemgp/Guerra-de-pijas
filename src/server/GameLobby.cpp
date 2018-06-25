//
// Created by rodrigo on 15/06/18.
//

#include <iostream>
#include <dirent.h>

#include "GameLobby.h"
#include "ServerSocket.h"
#include "Lobbies.h"
#include "Game.h"
#include "LobbyJoiner.h"
#include "Stage.h"

Worms::GameLobby::GameLobby(std::string port) :
        serverSocket(port.c_str()) {
    std::cout << "Se bindeo" << std::endl;
}

void Worms::GameLobby::start(std::string &stageFile) {
    try {
        std::string path("../res/");
        std::vector<std::vector<std::string>> levels;
        this->loadLevels(path, levels);

        Lobbies lobbies{levels};
        
        LobbyJoiner lobbyJoiner{lobbies, this->msgToJoiner};
        lobbyJoiner.start();
        int id = 0;

        while (!quit) {
            this->players.emplace_back(this->serverSocket.accept(), lobbies, id, this);
            this->players.back().start();
            id++;

            this->removePlayers();

            std::cout << "hubo una conexión" << std::endl;
        }
        this->removePlayers();
        
        this->msgToJoiner << IO::ServerInternalMsg{IO::ServerInternalAction::quit};
        lobbyJoiner.join();
        
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
            auto &lobby = dynamic_cast<Lobby &>(subject);

            /** En algún momento le tengo que sacar el socket al GameLobbyAssistant
             *  para crear un vector con los sockets de todos los jugadores, que es lo que
             *  recibe Game, entonces pienso que es mejor que sea al momento de iniciar la partida
             *  por si el jugador se arrepiente antes y quiere salir, que el Assistant lo pueda
             *  manejar.
             */

            const std::vector<int> &playerIDs = lobby.getPlayerIDs();
            for (auto &playerID : playerIDs) {
//                auto it = std::next(this->players.begin(), playerID);
                for (auto &player : this->players){
                    if ( player.getPlayerID() == playerID){
                        //TODO revisar el lugar donde se setea terminado el hilo
                        player.stop();
                        lobby.addPlayerSocket(std::move(player.getSocket()));
                    };
                }
            }
            lobby.start();

            break;
        }
        case Event::EndGame: {
            this->msgToJoiner << IO::ServerInternalMsg{IO::ServerInternalAction::lobbyFinished};
            break;
        }
        default: {
            break;
        }
    }
}

void Worms::GameLobby::removePlayers(){
    std::list<GameLobbyAssistant>::iterator playerIt;
    playerIt = this->players.begin();
    while (playerIt != this->players.end()){
        if (playerIt->itsOver()){
            playerIt->join();
            playerIt = this->players.erase(playerIt);
        } else {
            playerIt++;
        }
    }
}

void Worms::GameLobby::loadLevels(std::string &path, std::vector<std::vector<std::string>> &levels) {
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(path.c_str())) != NULL) {
        /* print all the files and directories within directory */
        while ((ent = readdir(dir)) != NULL) {
            if (std::string(ent->d_name)[0] != '.') {
                std::string levelPath(path + ent->d_name + "/");
//                std::cout << levelPath << std::endl;
                this->loadLevel(levelPath, levels);
            }
        }
        closedir (dir);
    } else {
        /* could not open directory */
        throw Exception("Could not open directory: &s", path.c_str());
    }
}

void Worms::GameLobby::loadLevel(std::string &path, std::vector<std::vector<std::string>> &levels) {
    DIR *dir;
    struct dirent *ent;
    std::vector<std::string> level;
    if ((dir = opendir(path.c_str())) != NULL) {
        /* print all the files and directories within directory */
        while ((ent = readdir(dir)) != NULL) {
            if (std::string(ent->d_name)[0] != '.') {
                std::string levelPath(path + ent->d_name);
//                std::cout << "\t" << levelPath << std::endl;

                level.emplace_back(std::move(levelPath));
            }
        }
        closedir (dir);
        levels.emplace_back(std::move(level));
    } else {
        /* could not open directory */
        throw Exception("Could not open directory: &s", path.c_str());
    }
}
