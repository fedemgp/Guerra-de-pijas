//
// Created by rodrigo on 16/06/18.
//

#ifndef INC_4_WORMS_LOBBY_H
#define INC_4_WORMS_LOBBY_H


#include <stdint-gcc.h>
#include <vector>
#include <CommunicationSocket.h>
#include "Subject.h"

namespace Worms {
    class Lobby : public Subject {
    public:
        Lobby(int playerID, uint8_t id);
        Lobby(Lobby &&other);

        void join(int playerID);
        uint8_t getPlayersQuantity() const;
        uint8_t getActualPlayers() const;
        const std::vector<int> &getPlayerIDs() const;
        uint8_t getID() const;
        void addPlayerSocket(CommunicationSocket &&player);

    private:
        const uint8_t id;
        uint8_t playersQuantity{2};
        uint8_t actualPlayers{0};
        std::vector<int> playerIDs;
        std::vector<CommunicationSocket> players;

        void startGame();
    };
}


#endif //INC_4_WORMS_LOBBY_H
