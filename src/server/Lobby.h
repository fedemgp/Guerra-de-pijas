//
// Created by rodrigo on 16/06/18.
//

#ifndef INC_4_WORMS_LOBBY_H
#define INC_4_WORMS_LOBBY_H


#include <stdint-gcc.h>
#include <vector>

namespace Worms {
    class Lobby {
    public:
        Lobby(int playerID, uint8_t id);

        void join(int playerID);
        uint8_t getPlayersQuantity() const;
        uint8_t getActualPlayers() const;
        const std::vector<int> &getPlayerIDs() const;
        uint8_t getID() const;
    private:
        const uint8_t id;
        uint8_t playersQuantity{2};
        uint8_t actualPlayers{0};
        std::vector<int> playerIDs;
    };
}


#endif //INC_4_WORMS_LOBBY_H
