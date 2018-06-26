//
// Created by rodrigo on 19/06/18.
//

#ifndef INC_4_WORMS_LOBBYJOINER_H
#define INC_4_WORMS_LOBBYJOINER_H


#include <GameStateMsg.h>
#include <Stream.h>
#include "Thread.h"
#include "Lobbies.h"

namespace Worms {
    class LobbyJoiner : public Thread {
    public:
        explicit LobbyJoiner(Worms::Lobbies &lobbies, IO::Stream<IO::ServerInternalMsg> &serverInput);

        void run() override;
        void stop() override;

    private:
        std::list<Lobby> &lobbies;
        IO::Stream<IO::ServerInternalMsg> &serverInput;
        bool finished{false};

        void handleServerInput(IO::ServerInternalMsg &msg);

        void killLobbies();
    };
}


#endif //INC_4_WORMS_LOBBYJOINER_H
