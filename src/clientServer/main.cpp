/*
 * Federico Manuel Gomez Peter
 * Date: 17/05/18.
 */
#include <exception>
#include <iostream>
#include <thread>

#include "client/GUIGame.h"
#include "server/Game.h"
#include "GameStateMsg.h"
#include "server/Stage.h"
#include "Stream.h"
#include "client/Window.h"

int main(int argc, const char *argv[]) {
    try {
        IO::Stream<IO::GameStateMsg> server_stream;
        IO::Stream<IO::PlayerInput> player_stream;
        GUI::Window window{};
        window.clear();

        Worms::Game game{Worms::Stage{}};
        std::thread game_thread =
            std::thread(std::bind(&Worms::Game::start, &game, &server_stream, &player_stream));

        GUI::Game gui_game{window, Worms::Stage{}};
        gui_game.start(&server_stream, &player_stream);

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
