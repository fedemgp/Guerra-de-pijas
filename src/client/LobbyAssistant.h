/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 17/06/18
 */

#ifndef __LOBBY_ASSISTANT_H__
#define __LOBBY_ASSISTANT_H__

#include <Protocol.h>
#include "ClientSocket.h"

namespace Worm{
    class LobbyAssistant{
    public:
        explicit LobbyAssistant(ClientSocket &socket);
        //TODO overrrite
        void run();

        ClientSocket getSocket();

    private:
        Protocol<ClientSocket> protocol;
        void clearScreen();
        void printCommands();
        void createGame();
        unsigned char command{0};
        std::uint8_t playersQuantity{0};

        void getGames();

        void joinGame();

        void waitGameStart();
    };
} //namespace Worm


#endif //__LOBBY_ASSISTANT_H__
