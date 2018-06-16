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
        Lobby(int playerID);

        void join(int playerID);

    private:
        uint8_t playersQuantity{2};
        uint8_t actualPlayers{0};
        std::vector<int> playerIDs;
    };
}


#endif //INC_4_WORMS_LOBBY_H
