//
// Created by rodrigo on 15/06/18.
//

#ifndef INC_4_WORMS_GAMELOBBY_H
#define INC_4_WORMS_GAMELOBBY_H


#define RESOURCE_PATH "../res/"

#include <list>
#include <string>

#include <CommunicationSocket.h>
#include <thread>
#include <GameStateMsg.h>
#include <Stream.h>
#include "ServerSocket.h"
#include "GameLobbyAssistant.h"

namespace Worms {
    class GameLobby : public Observer, public Thread {
    public:
        GameLobby(std::string port);
        GameLobby(GameLobby &copy) = delete;

        void run() override;
        void onNotify(Subject &subject, Event event) override;
        void stop() override;

    private:
        ServerSocket serverSocket;
        IO::Stream<IO::ServerInternalMsg> msgToJoiner;
        std::list<GameLobbyAssistant> players;
        bool quit{false};
        /**
         * @brief check if the GameLobbyAssistant thread is over. If so, join
         * it and erase it (because the sockets was already moved to the Lobby)
         */
        void removePlayers();

        void loadLevels(std::string &path, std::vector<IO::LevelData> &levels);

        void loadLevel(std::string &path, std::vector<IO::LevelData> &levels);

        void loadLevelBackground(std::string &path, IO::LevelData &level);

        void killPlayers();
    };
}


#endif //INC_4_WORMS_GAMELOBBY_H
