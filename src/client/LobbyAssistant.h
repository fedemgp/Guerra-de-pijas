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

    private:
        Protocol protocol;
        void clearScreen();
        void printCommands(std::vector<std::string> &vector);
        void createGame();
        unsigned char command{0};
        unsigned int playersQuantity{0};

        void getGames();

        void joinGame();
    };
} //namespace Worm


#endif //__LOBBY_ASSISTANT_H__
