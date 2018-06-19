//
// Created by rodrigo on 16/06/18.
//

#ifndef INC_4_WORMS_LOBBY_H
#define INC_4_WORMS_LOBBY_H


#include <stdint-gcc.h>
#include <vector>
#include <CommunicationSocket.h>
#include <mutex>
#include "Subject.h"
#include "Thread.h"

namespace Worms {
    class Lobby : public Thread, public Subject {
    public:
        Lobby(int playerID, std::uint8_t id);
        Lobby(Lobby &&other);
        Lobby(Lobby &copy) = delete;

        void run() override;
        void stop() override;

        void joinGame(int playerID);
        std::uint8_t getPlayersQuantity() const;
        std::uint8_t getActualPlayers() const;
        const std::vector<int> &getPlayerIDs() const;
        std::uint8_t getID() const;
        void addPlayerSocket(CommunicationSocket &&player);

    private:
        std::mutex mutex;
        const std::uint8_t id;
        std::uint8_t playersQuantity{2};
        std::uint8_t actualPlayers{0};
        std::vector<int> playerIDs;
        std::vector<CommunicationSocket> players;

        bool finished{false};
        bool gameStarted{false};
    };
}


#endif //INC_4_WORMS_LOBBY_H
