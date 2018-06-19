//
// Created by rodrigo on 19/06/18.
//

#ifndef INC_4_WORMS_LOBBYJOINER_H
#define INC_4_WORMS_LOBBYJOINER_H


#include "Thread.h"
#include "Lobbies.h"

namespace Worms {
    class LobbyJoiner : public Thread {
    public:
        explicit LobbyJoiner(Lobbies &lobbies);
        
        void run() override;
        void stop() override;

    private:
        std::list<Lobby> &lobbies;
        bool finished{false};
    };
}


#endif //INC_4_WORMS_LOBBYJOINER_H
