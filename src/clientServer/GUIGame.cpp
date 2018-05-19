/*
 * Created by Federico Manuel Gomez Peter
 * Date: 17/05/18.
 */

#include <SDL2/SDL.h>
#include <unistd.h>
#include <iostream>

#include "GUIGame.h"
#include "GameStateMsg.h"
#include "Stream.h"
#include "Window.h"

// TODO DEHARDCODE
GUI::Game::Game(Window &w) : window(w), texture_mgr(w.getRenderer()) {
    /* loads the required textures */
    this->texture_mgr.load(Worm::StateID::walk, "src/clientServer/assets/img/Worms/wwalk2.png",
                           GUI::Color{0x7f, 0x7f, 0xbb});
    this->texture_mgr.load(Worm::StateID::still, "src/clientServer/assets/img/Worms/wbrth1.png",
                           GUI::Color{0x7f, 0x7f, 0xbb});
}

GUI::Game::~Game() {}

void GUI::Game::start(IO::Stream<IO::GameStateMsg> *input, IO::Stream<IO::PlayerInput> *output) {
    try {
        // TODO: remove this
        this->worms.emplace_back(this->texture_mgr);

        uint32_t prev = SDL_GetTicks();
        IO::GameStateMsg m{1};
        bool quit = false;
        while (!quit) {
            /* handle events on queue */
            SDL_Event e;
            while (SDL_PollEvent(&e) != 0) {
                switch (e.type) {
                    case SDL_QUIT:
                        quit = true;
                        break;
                    case SDL_KEYDOWN:
                        this->worms[0].handleKeyDown(e.key.keysym.sym, output);
                        break;
                    case SDL_KEYUP:
                        this->worms[0].handleKeyUp(e.key.keysym.sym, output);
                        break;
                }
            }

            *input >> m;
            this->x = m.positions[0] * this->window.width;
            this->y = this->window.height - m.positions[1] * this->window.height;

            uint32_t current = SDL_GetTicks();
            float dt = static_cast<float>(current - prev) / 1000.0f;
            this->update(dt);
            prev = current;
            this->render();

            usleep(5 * 1000);
        }
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unkown error in GUI::Game::start()." << std::endl;
    }
}

void GUI::Game::update(float dt) {
    for (auto &worm : this->worms) {
        worm.update(dt);
    }
}

void GUI::Game::render() {
    this->window.clear();

    for (auto &worm : this->worms) {
        worm.render(this->x, this->y, this->window.getRenderer());
    }
    this->window.render();
}
