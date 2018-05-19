/*
 * Federico Manuel Gomez Peter
 * Date: 17/05/18.
 */
#include <exception>
#include <iostream>
#include <thread>

#include "GUIGame.h"
#include "Game.h"
#include "GameStateMsg.h"
#include "Stream.h"
#include "Window.h"
#include "World.h"

int main(int argc, const char *argv[]) {
    try {
        IO::Stream<IO::GameStateMsg> server_stream;
        IO::Stream<IO::PlayerInput> player_stream;
        GUI::Window window{};
        window.clear();

        Worms::Game game{Worms::World{}};
        std::thread game_thread =
            std::thread(std::bind(&Worms::Game::start, &game, &server_stream, &player_stream));

        std::cerr << "lalalasdsasdf fd" << std::endl;
        GUI::Game gui_game{window};
        std::cerr << "lalalasds" << std::endl;

        std::thread gui_thread =
            std::thread(std::bind(&GUI::Game::start, &gui_game, &server_stream, &player_stream));

        gui_thread.join();

        game.exit();
        game_thread.join();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Unkown error in main thread" << std::endl;
        return 1;
    }
    return 0;
}
