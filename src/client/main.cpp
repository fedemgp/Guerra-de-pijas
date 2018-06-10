/*
 * Created by Federico Manuel Gomez Peter
 * Date: 02/05/2018.
 */
#include <iostream>
#include <string>
#include <vector>

#include "ClientSocket.h"
#include "GUIGame.h"

int main() {
    try {
        std::string host = "localhost";
        std::string port = "1051";
        ClientSocket socket(host.data(), port.data());

        GUI::Window window{};
        window.clear();

        GUI::Game gui_game{window, Worms::Stage{}, socket};
        gui_game.start();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Unkown error in main thread" << std::endl;
        return 1;
    }
    return 0;
}
