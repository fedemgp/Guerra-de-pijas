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
#include "WrapTexture.h"
#include "Bullet.h"

// TODO DEHARDCODE
GUI::Game::Game(Window &w, Worms::Stage &&stage)
    : window(w),
      texture_mgr(w.getRenderer()),
      stage(stage),
      cam(this->scale, w.width, w.height, w.getRenderer()),
      font(TTF_OpenFont("src/clientServer/assets/fonts/gruen_lemonograf.ttf", 28)) {
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
    this->texture_mgr.load(GUI::GameTextures::Aim,
                           "src/clientServer/assets/img/Worms/wbaz.png",
                           GUI::Color{0x7f, 0x7f, 0xbb});
    this->texture_mgr.load(GUI::GameTextures::Missile,
                           "src/clientServer/assets/img/Weapons/missile.png",
                           GUI::Color{0x7f, 0x7f, 0xbb} );

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

GUI::Game::~Game() {
    TTF_CloseFont(this->font);
}

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

            if (m.shoot){
                if (this->bullet == nullptr) {
                    this->bullet = std::shared_ptr<Ammo::Bullet>(new Ammo::Bullet(this->texture_mgr));
                }
            }

            uint32_t current = SDL_GetTicks();
            float dt = static_cast<float>(current - prev) / 1000.0f;
            prev = current;

            float cur_x = this->snapshot.positions[this->snapshot.currentWorm * 2];
            float cur_y = this->snapshot.positions[this->snapshot.currentWorm * 2 + 1];

            /* move the camera to the current player */
            this->cam.moveTo(GUI::Position{cur_x, cur_y});

            this->update(dt);
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

    this->cam.update(dt);

    if (this->bullet != nullptr) {
        this->bullet->update(dt);
    }
}

void GUI::Game::render() {
    this->window.clear();

    for (uint8_t i = 0; i < this->snapshot.num_worms; i++) {
        float cur_x = this->snapshot.positions[i * 2];
        float cur_y = this->snapshot.positions[i * 2 + 1];

        /* convert to camera coordinates */
        this->worms[i].render(GUI::Position{cur_x, cur_y}, this->cam);
    }

    for (auto &girder : this->stage.getGirders()) {
        const GUI::Texture &texture = this->texture_mgr.get(GUI::GameTextures::LongGirder);

        int height = int(girder.height * float(this->scale));
        int width = int(girder.length * float(this->scale));

        GUI::WrapTexture wt{texture, width, height};
        wt.render(GUI::Position{girder.pos.x, girder.pos.y}, this->cam);
    }

    if (this->bullet != nullptr){
        int local_x = this->snapshot.bullet[0];
        int local_y = this->snapshot.bullet[1];
        this->bullet->setAngle(this->snapshot.bulletAngle);
        this->bullet->render(GUI::Position{local_x, local_y}, this->window.getRenderer());
    }

    /* displays the remaining turn time */
    int x = this->window.width / 2;
    int y = 20;

    SDL_Color color = {0, 0, 0};
    Text text{this->font};
    text.set(std::to_string(this->stage.turnTime - this->snapshot.elapsedTurnSeconds), color);
    text.renderFixed(ScreenPosition{x, y}, this->cam);

    this->window.render();
}
/**
 * @brief Draws the game controls.
 */
void GUI::Game::render_controls() {
    /* draws the remaining time */
}
