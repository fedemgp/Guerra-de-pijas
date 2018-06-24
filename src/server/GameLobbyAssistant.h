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
        GameLobbyAssistant(GameLobbyAssistant &copy) = delete;
        void run() override;
        void stop() override;
        bool itsOver() const;
        void onNotify(Subject &subject, Event event) override;
        int getPlayerID() const;
        CommunicationSocket getSocket();

    private:
        Protocol<CommunicationSocket> protocol;
        Lobbies &lobbies;
        int playerID;
        std::vector<Observer *> lobbyObservers;
        bool finished{false};

        void getLevels();
        void getGames();
        void joinGame();

        void createGame();
    };
}

#endif //INC_4_WORMS_GAMELOBBYASSISTANT_H
