//
// Created by rodrigo on 20/06/18.
//

#ifndef INC_4_WORMS_COMMUNICATIONPROTOCOL_H
#define INC_4_WORMS_COMMUNICATIONPROTOCOL_H


#include "ClientSocket.h"
#include <Protocol.h>
#include <Stream.h>
#include "Thread.h"

namespace IO {
    class CommunicationProtocol : public Thread {
    public:
        std::vector<LevelInfo> levelsInfo;
        std::vector<GameInfo> gamesInfo;

        explicit CommunicationProtocol(ClientSocket &socket, IO::Stream<IO::ClientGUIMsg> *clientStream,
                                               IO::Stream<IO::ServerResponse> *output);

        void run() override;
        void stop() override;

        ClientSocket getSocket();

    private:
        Protocol<ClientSocket> protocol;
        unsigned char command{0};
        std::uint8_t playersQuantity{0};
        IO::Stream<IO::ClientGUIMsg> *clientStream;
        IO::Stream<IO::ServerResponse> *output;
        bool quit{false};

        void startCreateGame();
        void getGames();
        void joinGame();
        void waitGameStart(int levelSelected);

        void handleClientInput(ClientGUIMsg &msg);

        void createGame(int levelSelected);
    };
}


#endif //INC_4_WORMS_COMMUNICATIONPROTOCOL_H
