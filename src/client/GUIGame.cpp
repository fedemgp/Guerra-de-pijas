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
GUI::Game::Game(Window &w, Worms::Stage &&stage, ClientSocket &socket, std::uint8_t team)
    : window(w),
      texture_mgr(w.getRenderer()),
      sound_effect_mgr(),
      stage(stage),
      cam(this->scale, w.getWidth(), w.getHeight(), w.getRenderer()),
      font("assets/fonts/gruen_lemonograf.ttf", 28),
      armory(this->texture_mgr, this->cam, this->font),
      socket(socket),
      team(team) {
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
    this->texture_mgr.load(GUI::GameTextures::Sliding, "assets/img/Worms/wslided.png",
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
    this->texture_mgr.load(GUI::GameTextures::WormAirAttack, "assets/img/Worms/wairtlk.png",
                           GUI::Color{0x7f, 0x7f, 0xbb});
    this->texture_mgr.load(GUI::GameTextures::AirMissile, "assets/img/Weapons/airmisl.png",
                           GUI::Color{0xc0, 0xc0, 0x80});
    this->texture_mgr.load(GUI::GameTextures::WormDynamite, "assets/img/Worms/wdynbak.png",
                           GUI::Color{0x7f, 0x7f, 0xbb});
    this->texture_mgr.load(GUI::GameTextures::Dynamite, "assets/img/Weapons/dynamite.png",
                           GUI::Color{0x7f, 0x7f, 0xbb});
    this->texture_mgr.load(GUI::GameTextures::WormBaseballBat, "assets/img/Worms/wbsbaim.png",
                           GUI::Color{0xc0, 0xc0, 0x80});
    this->texture_mgr.load(GUI::GameTextures::WormBaseballBatting, "assets/img/Worms/wbsbswn.png",
                           GUI::Color{0xc0, 0xc0, 0x80});
    this->texture_mgr.load(GUI::GameTextures::WormTeleport, "assets/img/Worms/wteltlk.png",
                           GUI::Color{0xc0, 0xc0, 0x80});
    this->texture_mgr.load(GUI::GameTextures::WormTeleporting, "assets/img/Worms/wteldsv.png",
                           GUI::Color{0xc0, 0xc0, 0x80});
    this->texture_mgr.load(GUI::GameTextures::BazookaIcon, "assets/img/Weapon Icons/bazooka.2.png",
                           GUI::Color{0x00, 0x00, 0x00});
    this->texture_mgr.load(GUI::GameTextures::GrenadeIcon, "assets/img/Weapon Icons/grenade.2.png",
                           GUI::Color{0x00, 0x00, 0x00});
    this->texture_mgr.load(GUI::GameTextures::ClusterIcon, "assets/img/Weapon Icons/cluster.2.png",
                           GUI::Color{0x00, 0x00, 0x00});
    this->texture_mgr.load(GUI::GameTextures::MortarIcon, "assets/img/Weapon Icons/mortar.2.png",
                           GUI::Color{0x00, 0x00, 0x00});
    this->texture_mgr.load(GUI::GameTextures::BananaIcon, "assets/img/Weapon Icons/banana.2.png",
                           GUI::Color{0x00, 0x00, 0x00});
    this->texture_mgr.load(GUI::GameTextures::HolyIcon, "assets/img/Weapon Icons/hgrenade.2.png",
                           GUI::Color{0x00, 0x00, 0x00});
    this->texture_mgr.load(GUI::GameTextures::AirIcon, "assets/img/Weapon Icons/airstrke.1.png",
                           GUI::Color{0x00, 0x00, 0x00});
    this->texture_mgr.load(GUI::GameTextures::DynamiteIcon,
                           "assets/img/Weapon Icons/dynamite.1.png", GUI::Color{0x00, 0x00, 0x00});
    this->texture_mgr.load(GUI::GameTextures::BaseballBatIcon,
                           "assets/img/Weapon Icons/baseball.1.png", GUI::Color{0x00, 0x00, 0x00});
    this->texture_mgr.load(GUI::GameTextures::TeleportIcon,
                           "assets/img/Weapon Icons/teleport.1.png", GUI::Color{0x00, 0x00, 0x00});

    this->armory.loadWeapons();

    this->sound_effect_mgr.load(GUI::GameSoundEffects::WalkCompress,
                                "assets/sound/Effects/Walk-Compress.wav");
    this->sound_effect_mgr.load(GUI::GameSoundEffects::WormJump,
                                "assets/sound/Soundbanks/JUMP1.WAV");
    this->sound_effect_mgr.load(GUI::GameSoundEffects::WormBackFlip,
                                "assets/sound/Soundbanks/JUMP2.WAV");
    this->sound_effect_mgr.load(GUI::GameSoundEffects::WormLanding,
                                "assets/sound/Effects/WormLanding.wav");
    this->sound_effect_mgr.load(GUI::GameSoundEffects::WormHit, "assets/sound/Soundbanks/OUCH.WAV");
    this->sound_effect_mgr.load(GUI::GameSoundEffects::WormDrowning,
                                "assets/sound/Effects/UnderWaterLoop.wav");
    this->sound_effect_mgr.load(GUI::GameSoundEffects::WormDie,
                                "assets/sound/Soundbanks/BYEBYE.WAV");
    this->sound_effect_mgr.load(GUI::GameSoundEffects::Splash, "assets/sound/Effects/Splash.wav");
    this->sound_effect_mgr.load(GUI::GameSoundEffects::Explosion,
                                "assets/sound/Effects/Explosion1.wav");
    this->sound_effect_mgr.load(GUI::GameSoundEffects::Holy,
                                "assets/sound/Effects/HOLYGRENADE.WAV");
    this->sound_effect_mgr.load(GUI::GameSoundEffects::AirStrike,
                                "assets/sound/Effects/Airstrike.wav");
    this->sound_effect_mgr.load(GUI::GameSoundEffects::Teleport,
                                "assets/sound/Effects/TELEPORT.WAV");
    this->sound_effect_mgr.load(GUI::GameSoundEffects::Shot,
                                "assets/sound/Effects/ROCKETRELEASE.WAV");
    this->sound_effect_mgr.load(GUI::GameSoundEffects::Banana,
                                "assets/sound/Effects/BananaImpact.wav");

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

    delete[] buffer;
}

void GUI::Game::outputWorker() {
    IO::PlayerMsg msg;
    char *buffer = new char[msg.getSerializedSize()];

    try {
        while (!this->quit) {
            this->output.pop(msg, true);
            msg.serialize(buffer, msg.getSerializedSize());
            this->socket.send(buffer, msg.getSerializedSize());
        }
    } catch (const std::exception &e) {
        std::cerr << "GUI::Game::outputWorker:" << e.what() << std::endl;
    }

    delete[] buffer;
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
                while (SDL_PollEvent(&e) != 0 && this->team == this->snapshot.currentTeam) {
                    switch (e.type) {
                        case SDL_QUIT:
                            this->exit();
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
                if (this->snapshot.bulletsQuantity == 0 && this->doesAnyoneShot) {
                    this->bullets.erase(this->bullets.begin(), this->bullets.end());
                    this->explodedQuantity = 0;
                    this->doesAnyoneShot = false;
                    this->worms[this->snapshot.currentWorm].reset();
                }
                if (this->snapshot.bulletsQuantity > 0) {
                    this->doesAnyoneShot = true;
                    for (int i = this->bullets.size(); i < this->snapshot.bulletsQuantity; i++) {
                        std::shared_ptr<Ammo::Bullet> p(new Ammo::Bullet(
                                this->texture_mgr, this->sound_effect_mgr, this->snapshot.bulletType[i]));
                        this->bullets.emplace_back(p);
                    }
                    int i = 0;
                    for (auto &bullet : this->bullets) {
                        if (this->snapshot.bulletType[i] == Worm::WeaponID::WExplode &&
                            !bullet->exploded()) {
                            bullet->madeImpact();
                            this->explodedQuantity++;
                        }
                        bullet->setAngle(this->snapshot.bulletsAngle[i++]);
                    }
                }

                uint32_t current = SDL_GetTicks();
                float dt = static_cast<float>(current - prev) / 1000.0f;
                prev = current;

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
                    float cur_follow_x =
                            this->snapshot.positions[this->snapshot.currentWormToFollow * 2];
                    float cur_follow_y =
                            this->snapshot.positions[this->snapshot.currentWormToFollow * 2 + 1];

                    /* move the camera to the current player */
                    this->cam.moveTo(GUI::Position{cur_follow_x, cur_follow_y});
                }

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
        worm.update(dt);
    }

    this->cam.update(dt);

    for (auto &bullet : this->bullets) {
        bullet->update(dt);
    }
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

    /* displays the remaining turn time */
    double turnTimeLeft = this->snapshot.currentPlayerTurnTime - this->snapshot.elapsedTurnSeconds;
    turnTimeLeft = (turnTimeLeft < 0.0f) ? 0.0f : turnTimeLeft;

    int x = this->window.getWidth() / 2;
    int y = 20;

    SDL_Color color = {0, 0, 0};
    Text text{this->font};
    text.set(std::to_string(static_cast<int>(turnTimeLeft)), color);
    text.renderFixed(ScreenPosition{x, y}, this->cam);
    this->armory.render();

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
