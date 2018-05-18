/*
 * Created by Federico Manuel Gomez Peter
 * Date: 17/05/18.
 */

#include "GUIGame.h"
#include <SDL2/SDL.h>
#include "GameStateMsg.h"
#include "Stream.h"
#include "Window.h"

// TODO DEHARDCODE
GUI::GUIGame::GUIGame(Window &w)
    : window(w),
      wwalk("src/prototype/assets/img/Worms/wwalk2.png", w.getRenderer(), Color{0x7f, 0x7f, 0xbb}) {
}

GUI::GUIGame::~GUIGame() {}

void GUI::GUIGame::start(IO::Stream<IO::GameStateMsg> *input, IO::Stream<IO::PlayerInput> *output) {
    uint32_t prev = SDL_GetTicks();
    IO::GameStateMsg m;
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
                    switch (e.key.keysym.sym) {
                        case SDLK_LEFT:
                            output->push(IO::PlayerInput::move_left);
                            this->wwalk.flip(SDL_FLIP_NONE);
                            break;
                        case SDLK_RIGHT:
                            output->push(IO::PlayerInput::move_right);
                            this->wwalk.flip(SDL_FLIP_HORIZONTAL);
                            break;
                    }
                    break;
                case SDL_KEYUP:
                    switch (e.key.keysym.sym) {
                        case SDLK_LEFT:
                        case SDLK_RIGHT:
                            output->push(IO::PlayerInput::stop_move);
                            break;
                    }
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
}

void GUI::GUIGame::update(float dt) {
    this->wwalk.update(dt);
}

void GUI::GUIGame::render() {
    this->window.clear();
    this->wwalk.render(this->window.getRenderer(), this->x, this->y);
    this->window.render();
}