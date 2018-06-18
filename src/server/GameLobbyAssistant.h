//
// Created by rodrigo on 15/06/18.
//

#ifndef INC_4_WORMS_GAMELOBBYASSISTANT_H
#define INC_4_WORMS_GAMELOBBYASSISTANT_H


#include <Protocol.h>
#include <sstream>

#include "Thread.h"
#include "Lobbies.h"

namespace Worms {
    class GameLobbyAssistant : public Thread {
    public:
        explicit GameLobbyAssistant(CommunicationSocket &communicationSocket, Lobbies &lobbies, int id);

        void run() override;
        void stop() override;

    private:
        Protocol protocol;
        Lobbies &lobbies;
        int id;
        void createGame();
        void getGames();
        void joinGame();
    };
}


#endif //INC_4_WORMS_GAMELOBBYASSISTANT_H
