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
        explicit LobbyAssistant(CommunicationSocket &socket);
        //TODO overrrite
        void run();

        CommunicationSocket getSocket();

    private:
        Protocol protocol;
        void clearScreen();
        void printCommands();
        void createGame();
        unsigned char command{0};
        unsigned int playersQuantity{0};

        void getGames();

        void joinGame();

        void waitGameStart();
    };
} //namespace Worm


#endif //__LOBBY_ASSISTANT_H__
