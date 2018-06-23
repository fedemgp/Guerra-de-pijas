/*
 * Created by Federico Manuel Gomez Peter
 * Date: 02/05/2018.
 */

#include <signal.h>
#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include "CommunicationSocket.h"
#include "Game.h"
#include "ServerSocket.h"

static volatile bool quit = false;

/**
 * @brief Signal handler.
 *
 * @param _ unused.
 */
static void _signal_handler(int _) {
    quit = true;
}

/**
 * @brief Thread handler that signals the Game to exit.
 *
 * @param game
 */
static void _exit_handler(Worms::Game &game) {
    while (!quit) {
        usleep(100000);
    }
    game.exit();
}

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        std::cout << "Usage: ./server PORT" << std::endl;
        return EXIT_FAILURE;
    }
    Game::Config &config = Game::Config::getInstance();
    std::cout << config.getWalkVelocity() << std::endl;
    try {
        /* sets a signal handler to exit the program gracefully */
        signal(SIGINT, _signal_handler);
        signal(SIGTERM, _signal_handler);

        std::string port(argv[1]);
        ServerSocket s(port.c_str());
        std::cout << "Se bindeo" << std::endl;

        /* get based on the number of players selected for the game */
        const uint8_t numTeams = 2;

        std::vector<CommunicationSocket> players;
        for (uint8_t i = 0; i < numTeams; i++) {
            players.push_back(s.accept());
            char buffer[1];
            buffer[0] = i;
            players.back().send(buffer, sizeof(buffer));
            std::cout << "hubo conexión" << std::endl;
        }

        std::cout << "game starts" << std::endl;
        Worms::Game game{Worms::Stage{}, players};

        std::thread exit_handler([&] { _exit_handler(game); });
        game.start();
        std::cout << "game ends" << std::endl;
        exit_handler.join();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Unkown error in main thread" << std::endl;
        return 1;
    }

    return EXIT_SUCCESS;
}
