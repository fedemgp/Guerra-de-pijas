//
// Created by rodrigo on 15/06/18.
//

#ifndef INC_4_WORMS_GAMELOBBY_H
#define INC_4_WORMS_GAMELOBBY_H


#include <list>
#include <string>

#include <CommunicationSocket.h>
#include <thread>
#include "ServerSocket.h"
#include "GameLobbyAssistant.h"

namespace Worms {
    class GameLobby {
    public:
        GameLobby(std::string port);

        void start();
        void exit();

    private:
        ServerSocket serverSocket;
        std::list<GameLobbyAssistant> players;
        bool quit{false};
    };
}


#endif //INC_4_WORMS_GAMELOBBY_H