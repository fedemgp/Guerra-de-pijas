/*
 * Created by Federico Manuel Gomez Peter
 * Date: 02/05/2018.
 */
#include <iostream>
#include <string>
#include <cstdlib>

#include "ClientSocket.h"
#include "GUIGame.h"
#include "LobbyAssistant.h"

int main(int argc, const char *argv[]) {
    if (argc != 3) {
        std::cout << "Usage: ./client HOST PORT" << std::endl;
        return EXIT_FAILURE;
    }

    try {
        std::string host = argv[1];
        std::string port = argv[2];
        ClientSocket socket(host.data(), port.data());

        //TODO start a thread running this
        Worm::LobbyAssistant lobby(socket);
        lobby.run();
        //TODO join Lobby thread
        GUI::Window window{};
        window.clear();

        socket = std::move(lobby.getSocket());

        char buffer[1];
        socket.receive(buffer, sizeof(buffer));

        GUI::Game game{window, Worms::Stage{}, socket, (std::uint8_t) buffer[0]};
        game.start();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Unkown error in main thread" << std::endl;
        return 1;
    }
    return 0;
}
