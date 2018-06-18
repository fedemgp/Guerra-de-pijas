//
// Created by rodrigo on 15/06/18.
//

#ifndef INC_4_WORMS_GAMELOBBYASSISTANT_H
#define INC_4_WORMS_GAMELOBBYASSISTANT_H


#include <Protocol.h>
#include <sstream>

#include "Thread.h"
#include "Lobbies.h"
#include "Observer.h"

namespace Worms {
    class GameLobbyAssistant : public Thread, public Observer {
    public:
        explicit GameLobbyAssistant(CommunicationSocket &&communicationSocket, Lobbies &lobbies, int id,
                                    Observer *lobbyObs);

        void run() override;
        void stop() override;
        void onNotify(Subject &subject, Event event) override;
        CommunicationSocket getSocket();

    private:
        Protocol protocol;
        Lobbies &lobbies;
        int id;
        std::vector<Observer *> lobbyObservers;

        void createGame();
        void getGames();
        void joinGame();
    };
}


#endif //INC_4_WORMS_GAMELOBBYASSISTANT_H
