//
// Created by rodrigo on 15/06/18.
//

#ifndef INC_4_WORMS_GAMELOBBY_H
#define INC_4_WORMS_GAMELOBBY_H


#include <list>
#include <string>

#include <CommunicationSocket.h>
#include <thread>
#include <GameStateMsg.h>
#include <Stream.h>
#include "ServerSocket.h"
#include "GameLobbyAssistant.h"

namespace Worms {
    class GameLobby : public Observer {
    public:
        GameLobby(std::string port);
        GameLobby(GameLobby &copy) = delete;

        void start(std::string &stageFile);
        void onNotify(Subject &subject, Event event) override;
        void exit();

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
        std::string splitpath(const std::string &str, const std::set<char> &delimiters);
        void loadLevelBackground(std::string &path, IO::LevelData &level);
    };
}


#endif //INC_4_WORMS_GAMELOBBY_H
