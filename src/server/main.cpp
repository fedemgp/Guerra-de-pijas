/*
 * Created by Federico Manuel Gomez Peter
 * Date: 02/05/2018.
 */

#include <iostream>
#include <string>
#include <vector>

#include "CommunicationSocket.h"
#include "Game.h"
#include "ServerSocket.h"

int main() {
    try {
        std::string port("1051");
        ServerSocket s(port.data());
        std::cout << "Se bindeo" << std::endl;

        /* get based on the number of players selected for the game */
        const uint8_t numTeams = 2;

        std::vector<CommunicationSocket> players;
        for (uint8_t i = 0; i < numTeams; i++) {
            players.push_back(s.accept());
            std::cout << "hubo conexión" << std::endl;
        }

        std::cout << "game starts" << std::endl;
        Worms::Game game{Worms::Stage{}, players};
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
