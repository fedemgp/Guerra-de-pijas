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
#include "GameLobby.h"

static volatile bool quit = false;

/**
 * @brief Signal handler.
 *
 * @param _ unused.
 */
static void _signal_handler(int _) {
    quit = true;
}

///**
// * @brief Thread handler that signals the Game to exit.
// *
// * @param game
// */
//static void _exit_handler(Worms::Game &game) {
//    while (!quit) {
//        usleep(100000);
//    }
//    game.exit();
//}

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        std::cout << "Usage: ./server PORT" << std::endl;
        return EXIT_FAILURE;
    }

    try {
        /* sets a signal handler to exit the program gracefully */
        signal(SIGINT, _signal_handler);
        signal(SIGTERM, _signal_handler);

        std::string port(argv[1]);
        Worms::GameLobby gameLobby{port};

        gameLobby.start();
        char quit{0};
        while (quit != 'q'){
            std::cin >> quit;
        }

        gameLobby.stop();
        gameLobby.join();

    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Unkown error in main thread" << std::endl;
        return 1;
    }

    return EXIT_SUCCESS;
}
