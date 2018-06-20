/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 17/06/18
 */

#ifndef __LOBBY_ASSISTANT_H__
#define __LOBBY_ASSISTANT_H__

#include <Protocol.h>
#include <memory>
#include "ClientSocket.h"
#include "GameWindow.h"

namespace GUI {
    class LobbyAssistant{
    public:
        explicit LobbyAssistant(ClientSocket &socket, Window &window);
        //TODO overrrite
        void run();

        ClientSocket getSocket();

    private:
        Protocol<ClientSocket> protocol;
        Window &window;
        void clearScreen();
        void printCommands();
        void createGame();
        unsigned char command{0};
        std::uint8_t playersQuantity{0};
        bool quit{false};
        std::shared_ptr<GameWindow> gameWindow{nullptr};

        void getGames();
        void joinGame();
        void waitGameStart();
    };
} //namespace Worm


#endif //__LOBBY_ASSISTANT_H__
