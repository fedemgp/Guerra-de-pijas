/*
 * Created by Federico Manuel Gomez Peter
 * Date: 17/05/18.
 */

#include <SDL2/SDL.h>
#include <unistd.h>
#include <iostream>

#include "Bullet.h"
#include "GUIGame.h"
#include "GameStateMsg.h"
#include "Stream.h"
#include "Text.h"
#include "Window.h"
#include "WrapTexture.h"

// TODO DEHARDCODE
GUI::Game::Game(Window &w, Worms::Stage &&stage, ClientSocket &socket)
    : window(w),
      texture_mgr(w.getRenderer()),
      stage(stage),
      cam(this->scale, w.getWidth(), w.getHeight(), w.getRenderer()),
      font("assets/fonts/gruen_lemonograf.ttf", 28),
      socket(socket) {
    /* loads the required textures */
    this->texture_mgr.load(GUI::GameTextures::WormWalk, "assets/img/Worms/wwalk2.png",
                           GUI::Color{0x7f, 0x7f, 0xbb});
    this->texture_mgr.load(GUI::GameTextures::WormIdle, "assets/img/Worms/wbrth1.png",
                           GUI::Color{0x7f, 0x7f, 0xbb});
    this->texture_mgr.load(GUI::GameTextures::LongGirder, "assets/img/Weapons/grdl4.png",
                           GUI::Color{0x7f, 0x7f, 0xbb});
    this->texture_mgr.load(GUI::GameTextures::StartJump, "assets/img/Worms/wjump.png",
                           GUI::Color{0x7f, 0x7f, 0xbb});
    this->texture_mgr.load(GUI::GameTextures::Jumping, "assets/img/Worms/wflyup.png",
                           GUI::Color{0x7f, 0x7f, 0xbb});
    this->texture_mgr.load(GUI::GameTextures::EndJump, "assets/img/Worms/wland2.png",
                           GUI::Color{0x7f, 0x7f, 0xbb});
    this->texture_mgr.load(GUI::GameTextures::BackFlipping, "assets/img/Worms/wbackflp.png",
                           GUI::Color{0x7f, 0x7f, 0xbb});
    this->texture_mgr.load(GUI::GameTextures::Falling, "assets/img/Worms/wfall.png",
                           GUI::Color{0x7f, 0x7f, 0xbb});
    this->texture_mgr.load(GUI::GameTextures::Bazooka, "assets/img/Worms/wbaz.png",
                           GUI::Color{0x7f, 0x7f, 0xbb});
    this->texture_mgr.load(GUI::GameTextures::Fly, "assets/img/Worms/wfly1.png",
                           GUI::Color{0x7f, 0x7f, 0xbb});
    this->texture_mgr.load(GUI::GameTextures::Die, "assets/img/Worms/wdie.png",
                           GUI::Color{0x7f, 0x7f, 0xbb});
    this->texture_mgr.load(GUI::GameTextures::Dead, "assets/img/Misc/grave4.png",
                           GUI::Color{0xC0, 0xC0, 0x80});
    this->texture_mgr.load(GUI::GameTextures::Missile, "assets/img/Weapons/missile.png",
                           GUI::Color{0x7f, 0x7f, 0xbb});
    this->texture_mgr.load(GUI::GameTextures::Explosion, "assets/img/Effects/circle25.png",
                           GUI::Color{0x80, 0x80, 0xC0});
    this->texture_mgr.load(GUI::GameTextures::Flame, "assets/img/Effects/flame1.png",
                           GUI::Color{0x80, 0x80, 0xC0});
    this->texture_mgr.load(GUI::GameTextures::Smoke, "assets/img/Effects/smkdrk20.png",
                           GUI::Color{0xC0, 0xC0, 0x80});
    this->texture_mgr.load(GUI::GameTextures::StaticBackground, "assets/img/background/static.png",
                           GUI::Color{0x7f, 0x7f, 0xbb});
    this->texture_mgr.load(GUI::GameTextures::Background1, "assets/img/background/bg1.png",
                           GUI::Color{0xff, 0xff, 0xff});
    this->texture_mgr.load(GUI::GameTextures::Background2, "assets/img/background/bg2.png",
                           GUI::Color{0xff, 0xff, 0xff});
    this->texture_mgr.load(GUI::GameTextures::Background3, "assets/img/background/bg3.png",
                           GUI::Color{0xff, 0xff, 0xff});
    this->texture_mgr.load(GUI::GameTextures::WormGrenade, "assets/img/Worms/wthrgrn.png",
                           GUI::Color{0x7f, 0x7f, 0xbb});
    this->texture_mgr.load(GUI::GameTextures::Grenade, "assets/img/Weapons/grenade.png",
                           GUI::Color{0x7f, 0x7f, 0xbb});
    this->texture_mgr.load(GUI::GameTextures::WormCluster, "assets/img/Worms/wthrcls.png",
                           GUI::Color{0x7f, 0x7f, 0xbb});
    this->texture_mgr.load(GUI::GameTextures::Cluster, "assets/img/Weapons/cluster.png",
                           GUI::Color{0x7f, 0x7f, 0xbb});
    this->texture_mgr.load(GUI::GameTextures::Mortar, "assets/img/Weapons/mortar.png",
                           GUI::Color{0xc0, 0xc0, 0x80});
    this->texture_mgr.load(GUI::GameTextures::Bazooka2, "assets/img/Worms/wbaz2.png",
                           GUI::Color{0xc0, 0xc0, 0x80});
    this->texture_mgr.load(GUI::GameTextures::Banana, "assets/img/Weapons/banana.png",
                           GUI::Color{0x7f, 0x7f, 0xbb});
    this->texture_mgr.load(GUI::GameTextures::WormBanana, "assets/img/Worms/wthrban.png",
                           GUI::Color{0x7f, 0x7f, 0xbb});
    this->texture_mgr.load(GUI::GameTextures::Holy, "assets/img/Weapons/hgrenade.png",
                           GUI::Color{0x7f, 0x7f, 0xbb});
    this->texture_mgr.load(GUI::GameTextures::WormHoly, "assets/img/Worms/wthrhgrd.png",
                           GUI::Color{0x7f, 0x7f, 0xbb});
    this->texture_mgr.load(GUI::GameTextures::Scope, "assets/img/Misc/crshairb.png",
                           GUI::Color{0x40, 0x40, 0x80});
    this->texture_mgr.load(GUI::GameTextures::Scope, "assets/img/Misc/crshairb.png",
                           GUI::Color{0x40, 0x40, 0x80});
    this->texture_mgr.load(GUI::GameTextures::PowerBar, "assets/img/Effects/blob.png",
                           GUI::Color{0x80, 0x80, 0xC0});
    this->texture_mgr.load(GUI::GameTextures::Fragment, "assets/img/Weapons/clustlet.png",
                           GUI::Color{0x7f, 0x7f, 0xbb});

    /* allocates space in the array to avoid the player addresses from changing */
    int num_worms = 0;
    this->worms.reserve(stage.getWorms().size());
    for (const auto &wormData : this->stage.getWorms()) {
        this->worms.emplace_back(num_worms, this->texture_mgr);
        this->snapshot.positions[num_worms * 2] = wormData.position.x;
        this->snapshot.positions[num_worms * 2 + 1] = wormData.position.y;
        this->snapshot.wormsHealth[num_worms] = wormData.health;
        num_worms += 1;
    }

    this->snapshot.num_worms = num_worms;
    //    this->snapshot.processingInputs = true;

    this->teamColors.push_back(SDL_Color{0xFF, 0, 0});
    this->teamColors.push_back(SDL_Color{0, 0xFF, 0});
    this->teamColors.push_back(SDL_Color{0, 0, 0xFF});

    this->inputThread = std::thread([this] { this->inputWorker(); });
    this->outputThread = std::thread([this] { this->outputWorker(); });
}

GUI::Game::~Game() {
    this->quit = true;
    this->outputThread.join();
    this->inputThread.join();
}

void GUI::Game::inputWorker() {
    IO::GameStateMsg msg;
    char *buffer = new char[msg.getSerializedSize()];

    try {
        while (!this->quit) {
            this->socket.receive(buffer, msg.getSerializedSize());
            msg.deserialize(buffer, msg.getSerializedSize());
            this->snapshotBuffer.set(msg);
            this->snapshotBuffer.swap();
        }
    } catch (const std::exception &e) {
        std::cerr << "GUI::Game::inputWorker:" << e.what() << std::endl;
    }

    delete buffer;
}

void GUI::Game::outputWorker() {
    IO::PlayerMsg msg;
    char *buffer = new char[msg.getSerializedSize()];

    try {
        while (!this->quit) {
            this->output.pop(msg);
            msg.serialize(buffer, msg.getSerializedSize());
            this->socket.send(buffer, msg.getSerializedSize());
        }
    } catch (const std::exception &e) {
        std::cerr << "GUI::Game::outputWorker:" << e.what() << std::endl;
    }

    delete buffer;
}

void GUI::Game::start() {
    try {
        uint32_t prev = SDL_GetTicks();
        while (!this->quit) {
            /* updates the snapshot */
            this->snapshot = this->snapshotBuffer.get();
            Worm::Worm &cur = this->worms[this->snapshot.currentWorm];

            /* handle events on queue */
            SDL_Event e;
            while (SDL_PollEvent(&e) != 0) {
                switch (e.type) {
                    case SDL_QUIT:
                        quit = true;
                        break;
                    case SDL_KEYDOWN:
                        if (this->snapshot.processingInputs) {
                            cur.handleKeyDown(e.key.keysym.sym, &this->output);
                        }
                        break;
                    case SDL_KEYUP:
                        if (this->snapshot.processingInputs) {
                            cur.handleKeyUp(e.key.keysym.sym, &this->output);
                        }
                        break;
                    case SDL_MOUSEBUTTONDOWN: {
                        int x, y;
                        SDL_GetMouseState(&x, &y);
                        GUI::Position global = this->cam.screenToGlobal(GUI::ScreenPosition{x, y});
                        cur.mouseButtonDown(global, &this->output);
                    }
                }
            }

            /* synchronizes the worms states with the server's */
            for (std::size_t i = 0; i < this->worms.size(); i++) {
                this->worms[i].setState(this->snapshot.stateIDs[i]);
                this->worms[i].setWeapon((i != this->snapshot.currentWorm)
                                             ? Worm::WeaponID::WNone
                                             : this->snapshot.activePlayerWeapon);
            }

            if (cur.getState() == Worm::StateID::Still &&
                cur.getWeaponID() != Worm::WeaponID::WNone) {
                cur.setWeaponAngle(this->snapshot.activePlayerAngle);
            }

            if (this->snapshot.bulletsQuantity > 0) {
                //                if (this->bullets == nullptr) {
                //                    this->bullet = std::shared_ptr<Ammo::Bullet>(
                //                        new Ammo::Bullet(this->texture_mgr,
                //                        this->snapshot.activePlayerWeapon));
                //                }
                for (int i = this->bullets.size(); i < this->snapshot.bulletsQuantity; i++) {
                    std::shared_ptr<Ammo::Bullet> p(
                        new Ammo::Bullet(this->texture_mgr, this->snapshot.bulletType[i]));
                    this->bullets.emplace_back(p);
                }
                int i = 0;
                for (auto &bullet : this->bullets) {
                    if (!bullet->exploding()) {
                        if (this->snapshot.bulletType[i] == Worm::WeaponID::WExplode) {
                            bullet->madeImpact();
                        }
                        bullet->setAngle(this->snapshot.bulletsAngle[i++]);
                    }
                }
            }
            //            } else {
            //
            //                if (this->bullet != nullptr) {
            //                    this->bullet->madeImpact();
            //                }
            //            }

            uint32_t current = SDL_GetTicks();
            float dt = static_cast<float>(current - prev) / 1000.0f;
            prev = current;

            /* move the camera to the current player */
            if (this->snapshot.bulletsQuantity > 0) {
                float cur_x = this->snapshot.bullets[0];
                float cur_y = this->snapshot.bullets[1];

                this->cam.moveTo(GUI::Position{cur_x, cur_y});
            } else {
                float cur_follow_x =
                    this->snapshot.positions[this->snapshot.currentWormToFollow * 2];
                float cur_follow_y =
                    this->snapshot.positions[this->snapshot.currentWormToFollow * 2 + 1];

                /* move the camera to the current player */
                this->cam.moveTo(GUI::Position{cur_follow_x, cur_follow_y});
            }

            this->update(dt);
            this->render();
        }
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl << "In GUI::Game::start" << std::endl;
    } catch (...) {
        std::cerr << "Unkown error in GUI::Game::start()." << std::endl;
    }
}

void GUI::Game::update(float dt) {
    /**
     * remove all finished bullets animation
     */
    this->bullets.remove_if(Ammo::ExplotionChekcer());

    for (auto &worm : this->worms) {
        worm.health = this->snapshot.wormsHealth[static_cast<int>(worm.id)];
        worm.update(dt);
    }

    this->cam.update(dt);

    //    if (this->bullet != nullptr) {
    //        this->bullet->update(dt);
    //    }
    for (auto &bullet : this->bullets) {
        bullet->update(dt);
    }
}

void GUI::Game::render() {
    this->renderBackground();
    //    this->window.clear(this->backgroundColor);

    for (uint8_t i = 0; i < this->snapshot.num_worms; i++) {
        float cur_x = this->snapshot.positions[i * 2];
        float cur_y = this->snapshot.positions[i * 2 + 1];

        GUI::Position p{cur_x, cur_y};
        this->worms[i].setPosition(p);
        this->worms[i].render(p, this->cam);
    }

    for (auto &girder : this->stage.getGirders()) {
        const GUI::Texture &texture = this->texture_mgr.get(GUI::GameTextures::LongGirder);

        GUI::WrapTexture wt{texture, girder.length, girder.height};
        wt.render(GUI::Position{girder.pos.x, girder.pos.y}, this->cam);
    }

    //    if (this->bullet != nullptr) {
    //        float local_x = this->snapshot.bullet[0];
    //        float local_y = this->snapshot.bullet[1];
    //        if (!this->bullet->exploding()) {
    //            this->bullet->setAngle(this->snapshot.bulletAngle);
    //            this->bullet->setPosition(GUI::Position{local_x, local_y});
    //        }
    //        this->bullet->render(GUI::Position{local_x, local_y}, this->cam);
    //        //TODO make observer pattern to clean this
    //        if (this->bullet->exploded()) {
    //            this->bullet = nullptr;
    //        }
    //    }
    int i = 0, j = 0;
    for (auto &bullet : this->bullets) {
        float local_x = this->snapshot.bullets[i++];
        float local_y = this->snapshot.bullets[i++];
        if (!bullet->exploding()) {
            bullet->setAngle(this->snapshot.bulletsAngle[j++]);
            bullet->setPosition(GUI::Position{local_x, local_y});
        }
        bullet->render(GUI::Position{local_x, local_y}, this->cam);
    }

    /* health bars are renderer after the worms so they appear on top */
    for (uint8_t i = 0; i < this->snapshot.num_worms; i++) {
        float cur_x = this->snapshot.positions[i * 2];
        float cur_y = this->snapshot.positions[i * 2 + 1];

        if (this->worms[i].getState() != Worm::StateID::Dead) {
            Text health{this->font};
            health.setBackground(SDL_Color{0, 0, 0});
            health.set(std::to_string(static_cast<int>(this->worms[i].health)),
                       this->teamColors[this->snapshot.wormsTeam[i]], 20);
            health.render(GUI::Position{cur_x, cur_y + 2.2f}, this->cam);
        }
    }

    /* displays the remaining turn time */
    double turnTimeLeft = this->snapshot.currentPlayerTurnTime - this->snapshot.elapsedTurnSeconds;
    turnTimeLeft = (turnTimeLeft < 0.0f) ? 0.0f : turnTimeLeft;

    int x = this->window.getWidth() / 2;
    int y = 20;

    SDL_Color color = {0, 0, 0};
    Text text{this->font};
    text.set(std::to_string(static_cast<int>(turnTimeLeft)), color);
    text.renderFixed(ScreenPosition{x, y}, this->cam);

    this->window.render();
}

/**
 * @brief Renders the background images using a parallax effect.
 *
 */
void GUI::Game::renderBackground() {
    this->window.clear(this->backgroundColor);

    /* draws a static image in the background (this image doesn't move) */
    const Texture &staticBgTex = this->texture_mgr.get(GameTextures::StaticBackground);
    WrapTexture staticBg{staticBgTex, 500.0f, 40.0f};  // TODO: use screen size
    staticBg.render(Position{0.0f, (staticBgTex.getHeight() / this->cam.getScale()) / 2},
                    this->cam);

    /* draws moving image further in the background */
    const Texture &Bg1Tex = this->texture_mgr.get(GameTextures::Background1);
    // TODO: use the stage size
    WrapTexture bg1{Bg1Tex, 500.0f, Bg1Tex.getHeight() / this->cam.getScale()};

    Position pos{0.0f, (Bg1Tex.getHeight() / this->cam.getScale()) / 2};
    pos.x += this->cam.getPosition().x * 0.8f;
    bg1.render(pos, this->cam);

    /* draws a moving image in the background at intermediate distance */
    const Texture &Bg2Tex = this->texture_mgr.get(GameTextures::Background2);
    // TODO: use the stage size
    WrapTexture bg2{Bg2Tex, 500.0f, Bg2Tex.getHeight() / this->cam.getScale()};

    pos = {0.0f, (Bg2Tex.getHeight() / this->cam.getScale()) / 2};
    pos.x += this->cam.getPosition().x * 0.6f;
    bg2.render(pos, this->cam);

    /* draws a moving image in the background at a closer distance */
    const Texture &Bg3Tex = this->texture_mgr.get(GameTextures::Background3);
    // TODO: use the stage size
    WrapTexture bg3{Bg3Tex, 500.0f, Bg3Tex.getHeight() / this->cam.getScale()};

    pos = {0.0f, (Bg3Tex.getHeight() / this->cam.getScale()) / 2};
    pos.x += this->cam.getPosition().x * 0.25f;
    bg3.render(pos, this->cam);
}

/**
 * @brief Draws the game controls.
 */
void GUI::Game::render_controls() {
    /* draws the remaining time */
}
