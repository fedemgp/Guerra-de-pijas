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

//        void clearScreen();
//        void printCommands();
        void createGame();
        void getGames();
        void joinGame();
        void waitGameStart();

        void handleClientInput(ClientGUIMsg &msg);
    };
}


#endif //INC_4_WORMS_COMMUNICATIONPROTOCOL_H
