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
    this->texture_mgr.load(GUI::GameTextures::BackFlipping,
                           "src/clientServer/assets/img/Worms/wbackflp.png",
                           GUI::Color{0x7f, 0x7f, 0xbb});
    this->texture_mgr.load(GUI::GameTextures::Aim, "src/clientServer/assets/img/Worms/wbaz.png",
                           GUI::Color{0x7f, 0x7f, 0xbb});

    /* allocates space in the array to avoid the player addresses from changing */
    char num_worms = 0;
    this->worms.reserve(stage.getWormPositions().size());
    for (const auto &worm_pos : this->stage.getWormPositions()) {
        this->worms.emplace_back(this->texture_mgr);
        this->snapshot.positions[num_worms * 2] = worm_pos.x;
        this->snapshot.positions[num_worms * 2 + 1] = worm_pos.y;
        num_worms += 1;
    }

    this->snapshot.num_worms = num_worms;
}

GUI::Game::~Game() {}

void GUI::Game::start(IO::Stream<IO::GameStateMsg> *serverResponse,
                      IO::Stream<IO::PlayerInput> *clientResponse) {
    try {
        uint32_t prev = SDL_GetTicks();
        bool quit = false;
        while (!quit) {
            *serverResponse >> this->snapshot;
            Worm::Worm &cur = this->worms[this->snapshot.currentWorm];

            /* handle events on queue */
            SDL_Event e;
            while (SDL_PollEvent(&e) != 0) {
                switch (e.type) {
                    case SDL_QUIT:
                        quit = true;
                        break;
                    case SDL_KEYDOWN:
                        cur.handleKeyDown(e.key.keysym.sym, clientResponse);
                        break;
                    case SDL_KEYUP:
                        cur.handleKeyUp(e.key.keysym.sym, clientResponse);
                        break;
                }
            }

            /* synchronizes the worms states with the server's */
            for (std::size_t i = 0; i < this->worms.size(); i++) {
                this->worms[i].setState(this->snapshot.stateIDs[i]);
            }

            if (cur.getState() == Worm::StateID::Bazooka) {
                cur.setAngle(this->snapshot.activePlayerAngle);
            }

            uint32_t current = SDL_GetTicks();
            float dt = static_cast<float>(current - prev) / 1000.0f;
            this->update(dt);
            prev = current;
            this->render();

            usleep(5 * 1000);
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

    float cur_x = this->snapshot.positions[this->snapshot.currentWorm * 2];
    float cur_y = this->snapshot.positions[this->snapshot.currentWorm * 2 + 1];

    /* camera centered in the player */
    this->camx = cur_x - (this->window.width / 2) / this->scale;
    this->camy = cur_y + (this->window.height / 2) / this->scale;

    for (uint8_t i; i < this->snapshot.num_worms; i++) {
        cur_x = this->snapshot.positions[i * 2];
        cur_y = this->snapshot.positions[i * 2 + 1];

        /* convert to camera coordinates */
        int local_x = (cur_x - this->camx) * this->scale;
        int local_y = (this->camy - cur_y) * this->scale;
        this->worms[i].render(local_x, local_y, this->window.getRenderer());
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
