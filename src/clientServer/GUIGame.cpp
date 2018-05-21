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
GUI::Game::Game(Window &w, Worms::Stage &&stage)
    : window(w), texture_mgr(w.getRenderer()), stage(stage) {
    /* loads the required textures */
    this->texture_mgr.load(GUI::GameTextures::WormWalk,
                           "src/clientServer/assets/img/Worms/wwalk2.png",
                           GUI::Color{0x7f, 0x7f, 0xbb});
    this->texture_mgr.load(GUI::GameTextures::WormIdle,
                           "src/clientServer/assets/img/Worms/wbrth1.png",
                           GUI::Color{0x7f, 0x7f, 0xbb});
    this->texture_mgr.load(GUI::GameTextures::LongGirder,
                           "src/clientServer/assets/img/Weapons/grdl4.png",
                           GUI::Color{0x7f, 0x7f, 0xbb});
    this->texture_mgr.load(GUI::GameTextures::StartJump,
                           "src/clientServer/assets/img/Worms/wjump.png",
                           GUI::Color{0x7f, 0x7f, 0xbb});
    this->texture_mgr.load(GUI::GameTextures::Jumping,
                           "src/clientServer/assets/img/Worms/wflyup.png",
                           GUI::Color{0x7f, 0x7f, 0xbb});
    this->texture_mgr.load(GUI::GameTextures::EndJump,
                           "src/clientServer/assets/img/Worms/wland2.png",
                           GUI::Color{0x7f, 0x7f, 0xbb});
}

GUI::Game::~Game() {}

void GUI::Game::start(IO::Stream<IO::GameStateMsg> *serverResponse,
                      IO::Stream<IO::PlayerInput> *clientResponse) {
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
                        this->worms[0].handleKeyDown(e.key.keysym.sym, clientResponse);
                        break;
                    case SDL_KEYUP:
                        this->worms[0].handleKeyUp(e.key.keysym.sym, clientResponse);
                        break;
                }
            }

            *serverResponse >> m;
            this->x = m.positions[0];
            this->y = m.positions[1];
            this->worms[0].setState(m.stateIDs[0]);

            uint32_t current = SDL_GetTicks();
            float dt = static_cast<float>(current - prev) / 1000.0f;
            this->update(dt);
            prev = current;
            this->render();

            usleep(5 * 1000);1.0
        }
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl << "In GUI::Game::start" << std::endl;
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

    /* camera centered in the player */
    this->camx = this->x - (this->window.width / 2) / this->scale;
    this->camy = this->y + (this->window.height / 2) / this->scale;

    for (auto &worm : this->worms) {
        /* convert to camera coordinates */
        int local_x = (this->x - this->camx) * this->scale;
        int local_y = (this->camy - this->y) * this->scale;
        worm.render(local_x, local_y, this->window.getRenderer());
    }

    for (auto &girder : this->stage.getGirderPositions()) {
        const GUI::Texture &texture = this->texture_mgr.get(GUI::GameTextures::LongGirder);

        SDL_Rect dst;
        dst.x = ((girder.x + this->stage.getWidth() / 2) - this->camx) * this->scale;
        dst.y = (this->camy - girder.y) * this->scale;

        texture.render(this->window.getRenderer(), dst);
    }

    this->window.render();
}
