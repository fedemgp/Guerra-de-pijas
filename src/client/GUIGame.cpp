/*
 * Created by Federico Manuel Gomez Peter
 * Date: 17/05/18.
 */

#include <SDL2/SDL.h>
#include <unistd.h>
#include <cmath>
#include <iostream>
#include <sstream>

#include "GUIGame.h"
#include "GameStateMsg.h"
#include "Stream.h"
#include "Text.h"
#include "Weapons/Bullet.h"
#include "Window.h"
#include "WrapTexture.h"

// TODO DEHARDCODE
GUI::Game::Game(Window &w, Worms::Stage &&stage, std::vector<std::string> &backgroundPaths, ClientSocket &socket,
                std::uint8_t team)
    : window(w),
      texture_mgr(w.getRenderer()),
      sound_effect_mgr(),
      stage(stage),
      cam(w, this->scale, this->stage.getWidth(), this->stage.getHeight()),
      font("assets/fonts/gruen_lemonograf.ttf", 28),
      armory(this->texture_mgr, this->cam, this->font),
      socket(socket),
      team(team),
      wind(this->texture_mgr, this->cam),
      water(this->texture_mgr) {

    this->loadTextureManager();
    this->loadSoundManager();
    this->loadBackgroundManager();

    /* updates the armory */
    this->armory.loadWeapons();
    /* allocates space in the array to avoid the player addresses from changing */
    int num_worms = 0;
    this->worms.reserve(stage.getWorms().size());
    for (const auto &wormData : this->stage.getWorms()) {
        this->worms.emplace_back(num_worms, this->texture_mgr, this->sound_effect_mgr);
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

    this->currentPlayerArrow = std::unique_ptr<GUI::Animation>(
        new GUI::Animation(this->texture_mgr.get(GUI::GameTextures::CurrentPlayerArrow), false));
    this->inputThread = std::thread([this] { this->inputWorker(); });
    this->outputThread = std::thread([this] { this->outputWorker(); });

//    this->backGroundMusicPlayer =
//            std::unique_ptr<GUI::BackgroundMusicPlayer>(new GUI::BackgroundMusicPlayer{
//                    this->background_music_mgr.get(GUI::GameBackgroundMusic::Original)});
//    this->backGroundMusicPlayer->play();
    this->backgroundMusic = &this->background_music_mgr.get(GUI::GameBackgroundMusic::MurderTrain);
    this->backgroundMusic->play();
}

GUI::Game::~Game() {
    this->exit();
    this->outputThread.join();
    this->inputThread.join();
}

void GUI::Game::inputWorker() {
    IO::GameStateMsg msg;
    try {
        while (!this->quit) {
            /* receives the size of the msg */
            std::uint32_t size(0);
            socket.receive((char *)&size, sizeof(std::uint32_t));
            size = ntohl(size);

            std::vector<char> buffer(size, 0);
            /* reads the raw data from the buffer */
            socket.receive(buffer.data(), size);

            std::string buff(buffer.data(), size);

            /* sets the struct data from the buffer */
            msg.deserialize(buff);
            this->snapshotBuffer.set(msg);
            this->snapshotBuffer.swap();
        }
    } catch (const std::exception &e) {
        std::cerr << "GUI::Game::inputWorker:" << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown error in GUI::Game::inputWorker()" << std::endl;
    }
}

void GUI::Game::outputWorker() {
    IO::PlayerMsg msg;
    try {
        while (!this->quit) {
            this->output.pop(msg, true);
            std::string buff = msg.serialize();
            std::uint32_t size = buff.size();
            std::uint32_t netSize = htonl(size);

            this->socket.send((char *)&netSize, sizeof(std::uint32_t));
            this->socket.send(buff.c_str(), size);
        }
    } catch (const std::exception &e) {
        std::cerr << "GUI::Game::outputWorker:" << e.what() << std::endl;
    }
}

void GUI::Game::start() {
    try {
        uint32_t prev = SDL_GetTicks();
        while (!this->quit) {
            /* updates the snapshot */
            this->snapshot = this->snapshotBuffer.get();
            if (!this->snapshot.gameEnded) {
                Worm::Worm &cur = this->worms[this->snapshot.currentWorm];

                /* handle events on queue */
                SDL_Event e;
                while (SDL_PollEvent(&e) != 0) {
                    switch (e.type) {
                        case SDL_QUIT:
                            this->exit();
                            break;
                        case SDL_KEYDOWN:
                            if (this->snapshot.processingInputs &&
                                this->team == this->snapshot.currentTeam) {
                                cur.handleKeyDown(e.key.keysym.sym, &this->output);
                            }
                            break;
                        case SDL_KEYUP:
                            if (this->snapshot.processingInputs &&
                                this->team == this->snapshot.currentTeam) {
                                cur.handleKeyUp(e.key.keysym.sym, &this->output);
                            }
                            break;
                        case SDL_MOUSEBUTTONDOWN: {
                            if (this->snapshot.processingInputs &&
                                this->team == this->snapshot.currentTeam) {
                                int x, y;
                                SDL_GetMouseState(&x, &y);
                                GUI::Position global =
                                    this->cam.screenToGlobal(GUI::ScreenPosition{x, y});
                                cur.mouseButtonDown(global, &this->output);
                                break;
                            }
                        }
                        default:
                            break;
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
                if (this->snapshot.bulletsQuantity == 0 && this->snapshot.playerUsedTool) {
                    this->bullets.erase(this->bullets.begin(), this->bullets.end());
                    this->explodedQuantity = 0;
                    this->worms[this->snapshot.currentWorm].reset();
                }
                if (this->snapshot.bulletsQuantity > 0) {
                    for (int i = this->bullets.size(); i < this->snapshot.bulletsQuantity; i++) {
                        std::shared_ptr<Ammo::Bullet> p(
                            new Ammo::Bullet(this->texture_mgr, this->sound_effect_mgr,
                                             this->snapshot.bulletType[i]));
                        this->bullets.emplace_back(p);
                    }
                    int i = 0;
                    for (auto &bullet : this->bullets) {
                        if (this->snapshot.bulletType[i] == Worm::WeaponID::WExplode &&
                            !bullet->exploding()) {
                            bullet->madeImpact();
                            this->explodedQuantity++;
                        }
                        bullet->setAngle(this->snapshot.bulletsAngle[i++]);
                    }
                }

                uint32_t current = SDL_GetTicks();
                float dt = static_cast<float>(current - prev) / 1000.0f;
                prev = current;

                this->handleCamera(dt);
                this->update(dt);
            }
            this->render();
        }
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl << "In GUI::Game::start" << std::endl;
    } catch (...) {
        std::cerr << "Unkown error in GUI::Game::start()." << std::endl;
    }
}

void GUI::Game::update(float dt) {
    for (auto &worm : this->worms) {
        worm.health = this->snapshot.wormsHealth[static_cast<int>(worm.id)];
        worm.direction = this->snapshot.wormsDirection[static_cast<int>(worm.id)];
        worm.update(dt);
    }
    if (this->snapshot.waitingForNextTurn) {
        this->armory.update(this->snapshot);
        this->currentPlayerArrow->update(dt);
    } else {
        this->currentPlayerArrow->setFrame(0);
    }

    this->cam.update(dt);

    for (auto &bullet : this->bullets) {
        bullet->update(dt);
    }

    this->water.update(dt);
}

void GUI::Game::render() {
    this->renderBackground();

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
        wt.render(GUI::Position{girder.pos.x, girder.pos.y}, girder.angle, this->cam);
    }

    int i = 0, j = 0;
    for (auto &bullet : this->bullets) {
        float local_x = this->snapshot.bullets[i++];
        float local_y = this->snapshot.bullets[i++];
        if (!bullet->exploding()) {
            bullet->setAngle(this->snapshot.bulletsAngle[j++]);
            bullet->setPosition(GUI::Position{local_x, local_y});
        }

        if (!bullet->exploded()) {
            bullet->render(GUI::Position{local_x, local_y}, this->cam);
        }
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

    this->water.render(this->cam);

    this->renderStatic();

    this->window.render();
}

/**
 * @brief interrupts all current game operations and leaves the main loop.
 *
 */
void GUI::Game::exit() {
    this->quit = true;
    this->output.close();
    this->socket.shutdown();
}

/**
 * @brief Renders the background images using a parallax effect.
 *
 */
void GUI::Game::renderBackground() {
    SDL_Color bgColor{this->stage.backgroundColor.r, this->stage.backgroundColor.g, this->stage.backgroundColor.b};
    this->window.clear(bgColor);

    /* draws moving image further in the background */
    const Texture &Bg1Tex = this->texture_mgr.get(GameTextures::Background1);
    // TODO: use the stage size
    WrapTexture bg1{Bg1Tex, this->stage.getWidth(), Bg1Tex.getHeight() / this->cam.getScale()};

    Position pos{0.0f, (Bg1Tex.getHeight() / this->cam.getScale()) / 2};
    pos.x += this->cam.getPosition().x * 0.8f;
    bg1.render(pos, this->cam);

    /* draws a moving image in the background at intermediate distance */
    const Texture &Bg2Tex = this->texture_mgr.get(GameTextures::Background2);
    // TODO: use the stage size
    WrapTexture bg2{Bg2Tex, this->stage.getWidth(), Bg2Tex.getHeight() / this->cam.getScale()};

    pos = {0.0f, (Bg2Tex.getHeight() / this->cam.getScale()) / 2};
    pos.x += this->cam.getPosition().x * 0.6f;
    bg2.render(pos, this->cam);

    /* draws a moving image in the background at a closer distance */
    const Texture &Bg3Tex = this->texture_mgr.get(GameTextures::Background3);
    // TODO: use the stage size
    WrapTexture bg3{Bg3Tex, this->stage.getWidth(), Bg3Tex.getHeight() / this->cam.getScale()};

    pos = {0.0f, (Bg3Tex.getHeight() / this->cam.getScale()) / 2};
    pos.x += this->cam.getPosition().x * 0.25f;
    bg3.render(pos, this->cam);
}

/**
 * @brief Draws the game controls.
 */
void GUI::Game::renderStatic() {

    /* render the arrow to notify the current player when wainting for next turn*/
    if (this->snapshot.waitingForNextTurn) {
        float cur_x = this->snapshot.positions[this->snapshot.currentWorm * 2];
        float cur_y = this->snapshot.positions[this->snapshot.currentWorm * 2 + 1];
        GUI::Position position = GUI::Position{cur_x, cur_y + 4.4f};
        this->currentPlayerArrow->render(position, this->cam, SDL_FLIP_NONE);
    }

    /* health bars of the team */
    uint8_t numTeams = this->snapshot.num_teams;
    int textHeight = 25;
    for (uint8_t i = 0; i < numTeams; i++) {
        Text health{this->font};
        std::ostringstream oss;
        oss << "Team " << i + 1 << ": " << this->snapshot.teamHealths[i];

        health.setBackground(SDL_Color{0, 0, 0});
        health.set(oss.str(), this->teamColors[i], textHeight);
        int x = this->window.getWidth() / 2;
        int y = this->window.getHeight() - (textHeight * (numTeams - i));
        health.renderFixed(ScreenPosition{x, y}, this->cam);
    }

    /* displays the remaining turn time */
    std::int16_t turnTimeLeft =
        this->snapshot.currentPlayerTurnTime - this->snapshot.elapsedTurnSeconds;
    turnTimeLeft = (turnTimeLeft < 0) ? 0 : turnTimeLeft;

    int x = this->window.getWidth() / 2;
    int y = 20;

    SDL_Color color = {0, 0, 0};
    Text text{this->font};
    text.set(std::to_string(turnTimeLeft), color);
    text.renderFixed(ScreenPosition{x, y}, this->cam);

    /* renders armory */
    this->armory.render();

    this->wind.render(this->snapshot.windIntensity, this->window.getWidth());

    if (this->snapshot.gameEnded) {
        int x = this->window.getWidth() / 2;
        int y = this->window.getHeight() / 2;
        Text textGameEnd{this->font};
        if (this->snapshot.winner == this->team) {
            textGameEnd.set(std::string("You Win!"), this->teamColors[this->team], 60);
        } else {
            textGameEnd.set(std::string("You Lose!"), this->teamColors[this->team], 60);
        }
        textGameEnd.renderFixed(ScreenPosition{x, y}, this->cam);
    }
}

/**
 * @brief Handles the camera actions.
 *
 * @param dt Seconds elapsed since the last call to this function.
 */
void GUI::Game::handleCamera(float dt) {
    this->lastCameraUpdate += dt;

    /* checks the mouse to see if the user wishes to move the camera */
    int mx, my;
    SDL_GetMouseState(&mx, &my);

    const float cameraSpeed = 15.0f;
    const int cameraMargin = 50;

    /* checks if the camera should be moved horizontally */
    if (this->window.containsMouse()) {
        if (mx < cameraMargin) {
            auto p = this->cam.getPosition() - GUI::Position{cameraSpeed, 0.0f} * dt;
            this->cam.moveTo(this->cam.getPosition() - GUI::Position{cameraSpeed, 0.0f} * dt);
            this->lastCameraUpdate = 0.0f;
        } else if (mx > this->window.getWidth() - cameraMargin) {
            this->cam.moveTo(this->cam.getPosition() + GUI::Position{cameraSpeed, 0.0f} * dt);
            this->lastCameraUpdate = 0.0f;
        }

        /* checks if the camera should be moved vertically */
        if (my < cameraMargin) {
            this->cam.moveTo(this->cam.getPosition() + GUI::Position{0.0f, cameraSpeed} * dt);
            this->lastCameraUpdate = 0.0f;
        } else if (my > this->window.getHeight() - cameraMargin) {
            this->cam.moveTo(this->cam.getPosition() - GUI::Position{0.0f, cameraSpeed} * dt);
            this->lastCameraUpdate = 0.0f;
        }
    }

    /* if the user hasn't changed the camera in a while, it becomes automatic again */
    if (this->lastCameraUpdate < 2.0f) {
        return;
    } else {
        /* avoids overflow */
        this->lastCameraUpdate = 2.0f;
    }

    /* move the camera to the current player */
    if (this->snapshot.bulletsQuantity > this->explodedQuantity) {
        float cur_x{0};
        float cur_y{0};
        int i{0};
        for (int j = 0; i < this->snapshot.bulletsQuantity; i++) {
            if (this->snapshot.bulletType[i] != Worm::WExplode) {
                cur_x = this->snapshot.bullets[j++];
                cur_y = this->snapshot.bullets[j];
                break;
            }
            j += 2;
        }

        this->cam.moveTo(GUI::Position{cur_x, cur_y});
    } else {
        float cur_follow_x = this->snapshot.positions[this->snapshot.currentWormToFollow * 2];
        float cur_follow_y = this->snapshot.positions[this->snapshot.currentWormToFollow * 2 + 1];

        /* move the camera to the current player */
        this->cam.moveTo(GUI::Position{cur_follow_x, cur_follow_y});
    }
}

void GUI::Game::loadTextureManager(){
    std::string path(ASSETS_PATH);
    /* loads the required textures */
    this->texture_mgr.load(GUI::GameTextures::CurrentPlayerArrow, path + "/img/Misc/arrowdnb.png",
                           GUI::Color{0x40, 0x40, 0x80});
    this->texture_mgr.load(GUI::GameTextures::WindLeft, path + "/img/Misc/windl.png",
                           GUI::Color{0x00, 0x00, 0x00});
    this->texture_mgr.load(GUI::GameTextures::WindRight, path + "/img/Misc/windr.png",
                           GUI::Color{0x00, 0x00, 0x00});
    this->texture_mgr.load(GUI::GameTextures::WormWalk, path + "/img/Worms/wwalk2.png",
                           GUI::Color{0x7f, 0x7f, 0xbb});
    this->texture_mgr.load(GUI::GameTextures::WormIdle, path + "/img/Worms/wbrth1.png",
                           GUI::Color{0x7f, 0x7f, 0xbb});
    this->texture_mgr.load(GUI::GameTextures::LongGirder, path + "/img/Weapons/grdl4.png",
                           GUI::Color{0x7f, 0x7f, 0xbb});
    this->texture_mgr.load(GUI::GameTextures::StartJump, path + "/img/Worms/wjump.png",
                           GUI::Color{0x7f, 0x7f, 0xbb});
    this->texture_mgr.load(GUI::GameTextures::Jumping, path + "/img/Worms/wflyup.png",
                           GUI::Color{0x7f, 0x7f, 0xbb});
    this->texture_mgr.load(GUI::GameTextures::EndJump, path + "/img/Worms/wland2.png",
                           GUI::Color{0x7f, 0x7f, 0xbb});
    this->texture_mgr.load(GUI::GameTextures::BackFlipping, path + "/img/Worms/wbackflp.png",
                           GUI::Color{0x7f, 0x7f, 0xbb});
    this->texture_mgr.load(GUI::GameTextures::Falling, path + "/img/Worms/wfall.png",
                           GUI::Color{0x7f, 0x7f, 0xbb});
    this->texture_mgr.load(GUI::GameTextures::Bazooka, path + "/img/Worms/wbaz.png",
                           GUI::Color{0x7f, 0x7f, 0xbb});
    this->texture_mgr.load(GUI::GameTextures::Fly, path + "/img/Worms/wfly1.png",
                           GUI::Color{0x7f, 0x7f, 0xbb});
    this->texture_mgr.load(GUI::GameTextures::Die, path + "/img/Worms/wdie.png",
                           GUI::Color{0x7f, 0x7f, 0xbb});
    this->texture_mgr.load(GUI::GameTextures::Sliding, path + "/img/Worms/wslided.png",
                           GUI::Color{0x7f, 0x7f, 0xbb});
    this->texture_mgr.load(GUI::GameTextures::Dead, path + "/img/Misc/grave4.png",
                           GUI::Color{0xC0, 0xC0, 0x80});
    this->texture_mgr.load(GUI::GameTextures::Missile, path + "/img/Weapons/missile.png",
                           GUI::Color{0x7f, 0x7f, 0xbb});
    this->texture_mgr.load(GUI::GameTextures::Explosion, path + "/img/Effects/circle25.png",
                           GUI::Color{0x80, 0x80, 0xC0});
    this->texture_mgr.load(GUI::GameTextures::Flame, path + "/img/Effects/flame1.png",
                           GUI::Color{0x80, 0x80, 0xC0});
    this->texture_mgr.load(GUI::GameTextures::Smoke, path + "/img/Effects/smkdrk20.png",
                           GUI::Color{0xC0, 0xC0, 0x80});
    this->texture_mgr.load(GUI::GameTextures::Background1, path + "/img/background/bg1.png",
                           GUI::Color{0xff, 0xff, 0xff});
    this->texture_mgr.load(GUI::GameTextures::Background2, path + "/img/background/bg2.png",
                           GUI::Color{0xff, 0xff, 0xff});
    this->texture_mgr.load(GUI::GameTextures::Background3, path + "/img/background/bg3.png",
                           GUI::Color{0xff, 0xff, 0xff});
    this->texture_mgr.load(GUI::GameTextures::WormGrenade, path + "/img/Worms/wthrgrn.png",
                           GUI::Color{0x7f, 0x7f, 0xbb});
    this->texture_mgr.load(GUI::GameTextures::Grenade, path + "/img/Weapons/grenade.png",
                           GUI::Color{0x7f, 0x7f, 0xbb});
    this->texture_mgr.load(GUI::GameTextures::WormCluster, path + "/img/Worms/wthrcls.png",
                           GUI::Color{0x7f, 0x7f, 0xbb});
    this->texture_mgr.load(GUI::GameTextures::Cluster, path + "/img/Weapons/cluster.png",
                           GUI::Color{0x7f, 0x7f, 0xbb});
    this->texture_mgr.load(GUI::GameTextures::Mortar, path + "/img/Weapons/mortar.png",
                           GUI::Color{0xc0, 0xc0, 0x80});
    this->texture_mgr.load(GUI::GameTextures::Bazooka2, path + "/img/Worms/wbaz2.png",
                           GUI::Color{0xc0, 0xc0, 0x80});
    this->texture_mgr.load(GUI::GameTextures::Banana, path + "/img/Weapons/banana.png",
                           GUI::Color{0x7f, 0x7f, 0xbb});
    this->texture_mgr.load(GUI::GameTextures::WormBanana, path + "/img/Worms/wthrban.png",
                           GUI::Color{0x7f, 0x7f, 0xbb});
    this->texture_mgr.load(GUI::GameTextures::Holy, path + "/img/Weapons/hgrenade.png",
                           GUI::Color{0x7f, 0x7f, 0xbb});
    this->texture_mgr.load(GUI::GameTextures::WormHoly, path + "/img/Worms/wthrhgrd.png",
                           GUI::Color{0x7f, 0x7f, 0xbb});
    this->texture_mgr.load(GUI::GameTextures::Scope, path + "/img/Misc/crshairb.png",
                           GUI::Color{0x40, 0x40, 0x80});
    this->texture_mgr.load(GUI::GameTextures::Scope, path + "/img/Misc/crshairb.png",
                           GUI::Color{0x40, 0x40, 0x80});
    this->texture_mgr.load(GUI::GameTextures::PowerBar, path + "/img/Effects/blob.png",
                           GUI::Color{0x80, 0x80, 0xC0});
    this->texture_mgr.load(GUI::GameTextures::Fragment, path + "/img/Weapons/clustlet.png",
                           GUI::Color{0x7f, 0x7f, 0xbb});
    this->texture_mgr.load(GUI::GameTextures::WormAirAttack, path + "/img/Worms/wairtlk.png",
                           GUI::Color{0x7f, 0x7f, 0xbb});
    this->texture_mgr.load(GUI::GameTextures::AirMissile, path + "/img/Weapons/airmisl.png",
                           GUI::Color{0xc0, 0xc0, 0x80});
    this->texture_mgr.load(GUI::GameTextures::WormDynamite, path + "/img/Worms/wdynbak.png",
                           GUI::Color{0x7f, 0x7f, 0xbb});
    this->texture_mgr.load(GUI::GameTextures::Dynamite, path + "/img/Weapons/dynamite.png",
                           GUI::Color{0x7f, 0x7f, 0xbb});
    this->texture_mgr.load(GUI::GameTextures::WormBaseballBat, path + "/img/Worms/wbsbaim.png",
                           GUI::Color{0xc0, 0xc0, 0x80});
    this->texture_mgr.load(GUI::GameTextures::WormBaseballBatting, path + "/img/Worms/wbsbswn.png",
                           GUI::Color{0xc0, 0xc0, 0x80});
    this->texture_mgr.load(GUI::GameTextures::WormTeleport, path + "/img/Worms/wteltlk.png",
                           GUI::Color{0xc0, 0xc0, 0x80});
    this->texture_mgr.load(GUI::GameTextures::WormTeleporting, path + "/img/Worms/wteldsv.png",
                           GUI::Color{0xc0, 0xc0, 0x80});
    this->texture_mgr.load(GUI::GameTextures::BazookaIcon, path + "/img/Weapon Icons/bazooka.2.png",
                           GUI::Color{0x00, 0x00, 0x00});
    this->texture_mgr.load(GUI::GameTextures::GrenadeIcon, path + "/img/Weapon Icons/grenade.2.png",
                           GUI::Color{0x00, 0x00, 0x00});
    this->texture_mgr.load(GUI::GameTextures::ClusterIcon, path + "/img/Weapon Icons/cluster.2.png",
                           GUI::Color{0x00, 0x00, 0x00});
    this->texture_mgr.load(GUI::GameTextures::MortarIcon, path + "/img/Weapon Icons/mortar.2.png",
                           GUI::Color{0x00, 0x00, 0x00});
    this->texture_mgr.load(GUI::GameTextures::BananaIcon, path + "/img/Weapon Icons/banana.2.png",
                           GUI::Color{0x00, 0x00, 0x00});
    this->texture_mgr.load(GUI::GameTextures::HolyIcon, path + "/img/Weapon Icons/hgrenade.2.png",
                           GUI::Color{0x00, 0x00, 0x00});
    this->texture_mgr.load(GUI::GameTextures::AirIcon, path + "/img/Weapon Icons/airstrke.1.png",
                           GUI::Color{0x00, 0x00, 0x00});
    this->texture_mgr.load(GUI::GameTextures::DynamiteIcon,
                           path + "/img/Weapon Icons/dynamite.1.png", GUI::Color{0x00, 0x00, 0x00});
    this->texture_mgr.load(GUI::GameTextures::BaseballBatIcon,
                           path + "/img/Weapon Icons/baseball.1.png", GUI::Color{0x00, 0x00, 0x00});
    this->texture_mgr.load(GUI::GameTextures::TeleportIcon,
                           path + "/img/Weapon Icons/teleport.1.png", GUI::Color{0x00, 0x00, 0x00});
    this->texture_mgr.load(GUI::GameTextures::Water,
                           path + "/img/background/water.png", GUI::Color{0x00, 0x00, 0x00});
}

void GUI::Game::loadSoundManager(){
    std::string path(ASSETS_PATH);
    this->sound_effect_mgr.load(GUI::GameSoundEffects::WalkCompress,
                                path + "/sound/Effects/Walk-Compress.wav");
    this->sound_effect_mgr.load(GUI::GameSoundEffects::WormJump,
                                path + "/sound/Soundbanks/JUMP1.WAV");
    this->sound_effect_mgr.load(GUI::GameSoundEffects::WormBackFlip,
                                path + "/sound/Soundbanks/JUMP2.WAV");
    this->sound_effect_mgr.load(GUI::GameSoundEffects::WormLanding,
                                path + "/sound/Effects/WormLanding.wav");
    this->sound_effect_mgr.load(GUI::GameSoundEffects::WormHit, path + "/sound/Soundbanks/OUCH.WAV");
    this->sound_effect_mgr.load(GUI::GameSoundEffects::WormDrowning,
                                path + "/sound/Effects/UnderWaterLoop.wav");
    this->sound_effect_mgr.load(GUI::GameSoundEffects::WormDie,
                                path + "/sound/Soundbanks/BYEBYE.WAV");
    this->sound_effect_mgr.load(GUI::GameSoundEffects::Splash, path + "/sound/Effects/Splash.wav");
    this->sound_effect_mgr.load(GUI::GameSoundEffects::Explosion,
                                path + "/sound/Effects/Explosion1.wav");
    this->sound_effect_mgr.load(GUI::GameSoundEffects::Holy,
                                path + "/sound/Effects/HOLYGRENADE.WAV");
    this->sound_effect_mgr.load(GUI::GameSoundEffects::AirStrike,
                                path + "/sound/Effects/Airstrike.wav");
    this->sound_effect_mgr.load(GUI::GameSoundEffects::Teleport,
                                path + "/sound/Effects/TELEPORT.WAV");
    this->sound_effect_mgr.load(GUI::GameSoundEffects::Shot,
                                path + "/sound/Effects/ROCKETRELEASE.WAV");
    this->sound_effect_mgr.load(GUI::GameSoundEffects::Banana,
                                path + "/sound/Effects/BananaImpact.wav");
}

void GUI::Game::loadBackgroundManager(){
    std::string path(ASSETS_PATH);
    this->background_music_mgr.load(GUI::GameBackgroundMusic::Original,
                                   path + "/sound/Background/background.wav");
    this->background_music_mgr.load(GUI::GameBackgroundMusic::MurderTrain, path + "/sound/Background/MurderTrain.wav");
}
