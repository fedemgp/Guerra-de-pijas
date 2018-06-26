//
// Created by rodrigo on 16/06/18.
//

#ifndef INC_4_WORMS_LOBBY_H
#define INC_4_WORMS_LOBBY_H


#include <stdint-gcc.h>
#include <string>
#include <vector>
#include <mutex>
#include <GameStateMsg.h>

#include "CommunicationSocket.h"
#include "Subject.h"
#include "Thread.h"

namespace Worms {
    class Lobby : public Thread, public Subject {
    public:
        Lobby(int playerID, std::uint8_t id, std::vector<Observer *> obs, const IO::LevelData level,
              const IO::LevelInfo levelInfo);
        Lobby(Lobby &&other) noexcept;
        Lobby(Lobby &copy) = delete;

        void run() override;
        void stop() override;
        bool itsOver(); 

        void joinGame(int playerID);
        const IO::LevelInfo & getLevelInfo() const;
        std::uint8_t getActualPlayers() const;
        const std::vector<int> &getPlayerIDs() const;
        std::uint8_t getID() const;
        void addLobbyObserver(Observer *lobbyObserver);
        void addPlayerSocket(CommunicationSocket &&player);

    private:
        std::mutex mutex;
        const std::uint8_t id;
        std::uint8_t actualPlayers{0};
        std::vector<int> playerIDs;
        std::vector<CommunicationSocket> players;
        std::vector<Observer *> obs;
        const IO::LevelData level;
        const IO::LevelInfo levelInfo;

        bool finished{false};
        bool gameStarted{false};
    };
}


#endif //INC_4_WORMS_LOBBY_H
