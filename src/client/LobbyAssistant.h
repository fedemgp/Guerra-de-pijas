/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 17/06/18
 */

#ifndef __LOBBY_ASSISTANT_H__
#define __LOBBY_ASSISTANT_H__

#include <Protocol.h>
#include <memory>
#include <Stream.h>
#include <Font.h>
#include <Camera.h>
#include "ClientSocket.h"
#include "CommunicationProtocol.h"
#include "Observer.h"
#include "Thread.h"
#include "GameWindow.h"
#include "GameStateMsg.h"

namespace GUI { // Había una forward declaration con GameWindow pero no hace falta parece.
    class LobbyAssistant : public Observer {
    public:
        std::string levelPath;
        std::vector<std::string> backgroundPath;
        
        explicit LobbyAssistant(Window &window);
        //TODO overrrite
        void run();
        void onNotify(Subject &subject, Event event) override;

        ClientSocket getSocket();

        Font & getFont();

        Camera & getCam();

    private:
        Window &window;
        float scale{13.0f};
        bool quit{false};
        std::shared_ptr<GameWindow> gameWindow{nullptr};
        std::shared_ptr<GameWindow> nextGameWindow{nullptr};
        Font font;
        Camera cam;
        std::shared_ptr<IO::CommunicationProtocol> communicationProtocol;
        IO::Stream<IO::ClientGUIMsg> output;
        IO::Stream<IO::ServerResponse> serverStream;

        void handleServerResponse(IO::ServerResponse &response);
    };
} //namespace Worm


#endif //__LOBBY_ASSISTANT_H__
