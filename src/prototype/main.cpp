#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <atomic>
#include <functional>
#include <iostream>
#include <list>
#include <memory>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <vector>
#include "Box2D/Box2D.h"
#include "Exception.h"
#include "gui.h"
#include "Game.h"

void _exit_handler(int s) {
//    quit = true;
}

int main() {
    try {
        signal(SIGINT, _exit_handler);
        signal(SIGTERM, _exit_handler);

        IO::Stream<IO::GameStateMsg> server_stream;
        IO::Stream<IO::PlayerInput> player_stream;

        GUI::Window window{};
        window.clear();

        Worms::Game game{Worms::World{}};
        std::thread game_thread =
            std::thread(std::bind(&Worms::Game::start, &game, &server_stream, &player_stream));

        GUI::Game gui_game{window};
        std::thread gui_thread =
            std::thread(std::bind(&GUI::Game::start, &gui_game, &server_stream, &player_stream));

        game_thread.join();

        game.exit();
        gui_thread.join();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
