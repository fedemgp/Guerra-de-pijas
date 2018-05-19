/*
 * Created by Federico Manuel Gomez Peter
 * Date: 17/05/18.
 */

#include <SDL2/SDL.h>
#include <iostream>

#include "GUIGame.h"
#include "GameStateMsg.h"
#include "Stream.h"
#include "Window.h"

// TODO DEHARDCODE
GUI::Game::Game(Window &w) : window(w), worm(w.getRenderer()) {}

GUI::Game::~Game() {}

void GUI::Game::start(IO::Stream<IO::GameStateMsg> *input, IO::Stream<IO::PlayerInput> *output) {
    try {
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
                        this->worm.handleKeyDown(e.key.keysym.sym, output);
                        break;
                    case SDL_KEYUP:
                        this->worm.handleKeyUp(e.key.keysym.sym, output);
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
        }
    } catch (std::exception &e){
        std::cerr << e.what() << std::endl;
    } catch (...){
        std::cerr << "Unkown error in GUI::Game::start()." << std::endl;
    }
}

void GUI::Game::update(float dt) {
    this->worm.update(dt);
}

void GUI::Game::render() {
    this->window.clear();
    this->worm.render(this->x, this->y);
    this->window.render();
}