/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 18/05/18
 */

#include <SDL2/SDL_system.h>
#include <cmath>
#include <iostream>

#include "GameStateMsg.h"
#include "Text.h"
#include "Weapons/AerialAttack.h"
#include "Weapons/Banana.h"
#include "Weapons/BaseballBat.h"
#include "Weapons/Bazooka.h"
#include "Weapons/Cluster.h"
#include "Weapons/Dynamite.h"
#include "Weapons/Grenade.h"
#include "Weapons/Holy.h"
#include "Weapons/Mortar.h"
#include "Weapons/Teleport.h"
#include "Weapons/WeaponNone.h"
#include "Worm.h"
#include "WormState/BackFlip.h"
#include "WormState/Batting.h"
#include "WormState/Dead.h"
#include "WormState/Die.h"
#include "WormState/Drowning.h"
#include "WormState/Falling.h"
#include "WormState/Hit.h"
#include "WormState/Land.h"
#include "WormState/Sliding.h"
#include "WormState/Teleported.h"
#include "WormState/Teleporting.h"
#include "WormState/WormBackFlipping.h"
#include "WormState/WormEndBackFlip.h"
#include "WormState/WormEndJump.h"
#include "WormState/WormJumping.h"
#include "WormState/WormStartJump.h"
#include "WormState/WormStill.h"
#include "WormState/WormWalk.h"

Worm::Worm::Worm(ID id, const GUI::GameTextureManager &texture_mgr,
                 const GUI::GameSoundEffectManager &sound_effect_mgr)
    : id(id),
      texture_mgr(texture_mgr),
      sound_effect_mgr(sound_effect_mgr),
      animation(texture_mgr.get(GUI::GameTextures::WormIdle)) {
    this->setState(::Worm::StateID::Still);
    this->weapon = std::shared_ptr<Weapon>(new Bazooka(texture_mgr));
}

void Worm::Worm::handleKeyDown(SDL_Keycode key, IO::Stream<IO::PlayerMsg> *out) {
    IO::PlayerInput i = IO::PlayerInput::moveNone;
    switch (key) {
        case SDLK_RIGHT:
            i = this->state->moveRight(*this);
            break;
        case SDLK_LEFT:
            i = this->state->moveLeft(*this);
            break;
        case SDLK_UP:
            i = this->state->pointUp(*this);
            break;
        case SDLK_DOWN:
            i = this->state->pointDown(*this);
            break;
        case SDLK_RETURN:
            i = this->state->jump(*this);
            break;
        case SDLK_BACKSPACE:
            i = this->state->backFlip(*this);
            break;
        case SDLK_1:
            i = this->state->setTimeoutTo(*this, 1);
            break;
        case SDLK_2:
            i = this->state->setTimeoutTo(*this, 2);
            break;
        case SDLK_3:
            i = this->state->setTimeoutTo(*this, 3);
            break;
        case SDLK_4:
            i = this->state->setTimeoutTo(*this, 4);
            break;
        case SDLK_5:
            i = this->state->setTimeoutTo(*this, 5);
            break;
        case SDLK_F1:
            i = this->state->bazooka(*this);
            break;
        case SDLK_F2:
            i = this->state->grenade(*this);
            break;
        case SDLK_F3:
            i = this->state->cluster(*this);
            break;
        case SDLK_F4:
            i = this->state->mortar(*this);
            break;
        case SDLK_F5:
            i = this->state->banana(*this);
            break;
        case SDLK_F6:
            i = this->state->holy(*this);
            break;
        case SDLK_F7:
            i = this->state->aerialAttack(*this);
            break;
        case SDLK_F8:
            i = this->state->dynamite(*this);
            break;
        case SDLK_F9:
            i = this->state->baseballBat(*this);
            break;
        case SDLK_F10:
            i = this->state->teleport(*this);
            break;
        case SDLK_SPACE:
            i = this->state->startShot(*this);
            break;
    }
    if (i != IO::PlayerInput::moveNone) {
        IO::PlayerMsg msg;
        msg.input = i;
        *out << msg;
    }
}

void Worm::Worm::handleKeyUp(SDL_Keycode key, IO::Stream<IO::PlayerMsg> *out) {
    IO::PlayerInput i = IO::PlayerInput::moveNone;
    switch (key) {
        case SDLK_RIGHT:
            i = this->state->stopMove(*this);
            break;
        case SDLK_LEFT:
            i = this->state->stopMove(*this);
            break;
        case SDLK_SPACE:
            i = this->state->endShot(*this);
            break;
    }
    if (i != IO::PlayerInput::moveNone) {
        IO::PlayerMsg msg;
        msg.input = i;
        *out << msg;
    }
}

void Worm::Worm::render(GUI::Position &p, GUI::Camera &cam) {
    SDL_RendererFlip flipType =
        this->direction == Direction::left ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
    if (this->state->getState() != StateID::Still ||
        this->weapon->getWeaponID() == WeaponID::WNone) {
        this->animation.render(p, cam, flipType);
    } else {
        this->weapon->render(p, cam, flipType);
    }
    if (this->explosion != nullptr) {
        this->explosion->render(cam);
        if (this->explosion->finished()) {
            this->explosion = nullptr;
        }
    }
}

void Worm::Worm::update(float dt) {
    this->state->update(dt);
    this->animation.update(dt);
    this->weapon->update(dt);
    if (this->explosion != nullptr) {
        this->explosion->update(dt);
    }
    if (this->soundEffectPlayer != nullptr) {
        this->soundEffectPlayer->update(dt);
    }
}

GUI::Animation Worm::Worm::getAnimation(StateID state) const {
    switch (state) {
        case StateID::Still:
            break;
        case StateID::Walk:
            return GUI::Animation{this->texture_mgr.get(GUI::GameTextures::WormWalk)};
        case StateID::StartBackFlip:
        case StateID::StartJump:
            return GUI::Animation{this->texture_mgr.get(GUI::GameTextures::StartJump), true};
        case StateID::Jumping:
            return GUI::Animation{this->texture_mgr.get(GUI::GameTextures::Jumping)};
        case StateID::Land:
        case StateID::EndBackFlip:
        case StateID::EndJump:
            return GUI::Animation{this->texture_mgr.get(GUI::GameTextures::EndJump), true};
        case StateID::BackFlipping: {
            GUI::Animation animation{this->texture_mgr.get(GUI::GameTextures::BackFlipping)};
            animation.setAnimateOnce();
            return animation;
        }
        case StateID::Falling: {
            GUI::Animation animation{this->texture_mgr.get(GUI::GameTextures::Falling), true};
            animation.setAnimateOnce();
            return animation;
        }
        case StateID::Batting: {
            GUI::Animation animation{this->texture_mgr.get(GUI::GameTextures::WormBaseballBatting),
                                     false, 25, false};
            //            animation.setAnimateOnce();
            return animation;
        }
        case StateID::Teleporting: {
            GUI::Animation animation{this->texture_mgr.get(GUI::GameTextures::WormTeleporting),
                                     true};
            animation.setAnimateOnce();
            return animation;
        }
        case StateID::Teleported: {
            GUI::Animation animation{this->texture_mgr.get(GUI::GameTextures::WormTeleporting),
                                     true};
            animation.setPlayInverse();
            return animation;
        }
        case StateID::Hit:
            return GUI::Animation{this->texture_mgr.get(GUI::GameTextures::Fly), true,
                                  FLY_CENTER_FRAME, false};
        case StateID::Die: {
            GUI::Animation animation{this->texture_mgr.get(GUI::GameTextures::Die)};
            animation.setAnimateOnce();
            return animation;
        }
        case StateID::Drowning:
            return GUI::Animation{this->texture_mgr.get(GUI::GameTextures::Fly), true,
                                  DROWN_CENTER_FRAME, false};
        case StateID::Dead:
            return GUI::Animation{this->texture_mgr.get(GUI::GameTextures::Dead), true};
        case StateID::Sliding:
            return GUI::Animation{this->texture_mgr.get(GUI::GameTextures::Sliding), true};
    }
    return GUI::Animation{this->texture_mgr.get(GUI::GameTextures::WormIdle), true};
}

void Worm::Worm::playSoundEffect(StateID state) {
    this->soundEffectPlayer = nullptr;
    switch (state) {
        case StateID::Still:
            break;
        case StateID::Walk:
            this->soundEffectPlayer =
                std::shared_ptr<GUI::SoundEffectPlayer>(new GUI::SoundEffectPlayer{
                    this->sound_effect_mgr.get(GUI::GameSoundEffects::WalkCompress), 0.7f});
            this->soundEffectPlayer->update(0.3f);
            break;
        case StateID::StartBackFlip:
            this->soundEffectPlayer =
                std::shared_ptr<GUI::SoundEffectPlayer>(new GUI::SoundEffectPlayer{
                    this->sound_effect_mgr.get(GUI::GameSoundEffects::WormBackFlip), true});
            this->soundEffectPlayer->play();
            break;
        case StateID::StartJump:
            this->soundEffectPlayer =
                std::shared_ptr<GUI::SoundEffectPlayer>(new GUI::SoundEffectPlayer{
                    this->sound_effect_mgr.get(GUI::GameSoundEffects::WormJump), true});
            this->soundEffectPlayer->play();
            break;
        case StateID::Jumping:
            break;
        case StateID::EndBackFlip:
        case StateID::EndJump:
        case StateID::Land:
            this->soundEffectPlayer =
                std::shared_ptr<GUI::SoundEffectPlayer>(new GUI::SoundEffectPlayer{
                    this->sound_effect_mgr.get(GUI::GameSoundEffects::WormLanding), true});
            this->soundEffectPlayer->play();
            break;
        case StateID::BackFlipping:
            break;
        case StateID::Falling:
            break;
        case StateID::Batting:
            break;
        case StateID::Teleporting:
            break;
        case StateID::Teleported:
            break;
        case StateID::Hit:
            this->soundEffectPlayer =
                std::shared_ptr<GUI::SoundEffectPlayer>(new GUI::SoundEffectPlayer{
                    this->sound_effect_mgr.get(GUI::GameSoundEffects::WormHit), true});
            this->soundEffectPlayer->play();
            break;
        case StateID::Die:
            this->soundEffectPlayer =
                std::shared_ptr<GUI::SoundEffectPlayer>(new GUI::SoundEffectPlayer{
                    this->sound_effect_mgr.get(GUI::GameSoundEffects::WormDie), true});
            this->soundEffectPlayer->play();
            break;
        case StateID::Drowning:
            this->soundEffectPlayer =
                std::shared_ptr<GUI::SoundEffectPlayer>(new GUI::SoundEffectPlayer{
                    this->sound_effect_mgr.get(GUI::GameSoundEffects::WormDrowning)});
            break;
        case StateID::Dead:
            this->soundEffectPlayer =
                std::shared_ptr<GUI::SoundEffectPlayer>(new GUI::SoundEffectPlayer{
                    this->sound_effect_mgr.get(GUI::GameSoundEffects::Explosion), true});
            this->soundEffectPlayer->play();
            break;
        case StateID::Sliding:
            break;
    }
}

void Worm::Worm::setState(StateID state) {
    if (this->state == nullptr || this->state->getState() != state) {
        this->animation = this->getAnimation(state);
        this->playSoundEffect(state);

        /* creates the right state type */
        switch (state) {
            case StateID::Still:
                this->state = std::shared_ptr<State>(new Still());
                break;
            case StateID::Walk:
                this->state = std::shared_ptr<State>(new Walk());
                break;
            case StateID::StartJump:
                this->state = std::shared_ptr<State>(new StartJump());
                break;
            case StateID::Jumping:
                this->state = std::shared_ptr<State>(new Jumping());
                break;
            case StateID::EndJump:
                this->state = std::shared_ptr<State>(new EndJump());
                break;
            case StateID::StartBackFlip:
                this->state = std::shared_ptr<State>(new BackFlip());
                break;
            case StateID::BackFlipping:
                this->state = std::shared_ptr<State>(new BackFlipping());
                break;
            case StateID::EndBackFlip:
                this->state = std::shared_ptr<State>(new EndBackFlip());
                break;
            case StateID::Falling:
                this->state = std::shared_ptr<State>(new Falling());
                break;
            case StateID::Land:
                this->state = std::shared_ptr<State>(new Land());
                break;
            case StateID::Batting:
                this->state = std::shared_ptr<State>(new Batting());
                break;
            case StateID::Teleporting:
                this->state = std::shared_ptr<State>(new Teleporting());
                break;
            case StateID::Teleported:
                this->state = std::shared_ptr<State>(new Teleported());
                break;
            case StateID::Hit:
                this->state = std::shared_ptr<State>(new Hit());
                break;
            case StateID::Die:
                this->state = std::shared_ptr<State>(new Die());
                break;
            case StateID::Drowning:
                this->state = std::shared_ptr<State>(new Drowning());
                break;
            case StateID::Dead:
                this->state = std::shared_ptr<State>(new Dead());
                this->explosion = std::shared_ptr<Explosion>(new Explosion(this->texture_mgr));
                this->explosion->position = this->position;
                break;
            case StateID::Sliding:
                this->state = std::shared_ptr<State>(new Sliding());
                break;
        }
    }
}

Worm::StateID &Worm::Worm::getState() const {
    return this->state->getState();
}

void Worm::Worm::setWeapon(const WeaponID &id) {
    //    this->weapon.setWeapon(id);
    if (this->weapon->getWeaponID() != id) {
        switch (id) {
            case WeaponID::WBazooka:
                this->weapon = std::shared_ptr<Weapon>(new Bazooka(this->texture_mgr));
                break;
            case WeaponID::WGrenade:
                this->weapon = std::shared_ptr<Weapon>(new Grenade(this->texture_mgr));
                break;
            case WeaponID::WCluster:
                this->weapon = std::shared_ptr<Weapon>(new Cluster(this->texture_mgr));
                break;
            case WeaponID::WMortar:
                this->weapon = std::shared_ptr<Weapon>(new Mortar(this->texture_mgr));
                break;
            case WeaponID::WBanana:
                this->weapon = std::shared_ptr<Weapon>(new Banana(this->texture_mgr));
                break;
            case WeaponID::WHoly:
                this->weapon = std::shared_ptr<Weapon>(new Holy(this->texture_mgr));
                break;
            case WeaponID::WAerial:
                this->weapon = std::shared_ptr<Weapon>(new AerialAttack(this->texture_mgr));
                break;
            case WeaponID::WDynamite:
                this->weapon = std::shared_ptr<Weapon>(new Dynamite(this->texture_mgr));
                break;
            case WeaponID::WBaseballBat:
                this->weapon = std::shared_ptr<Weapon>(new BaseballBat(this->texture_mgr));
                break;
            case WeaponID::WTeleport:
                this->weapon = std::shared_ptr<Weapon>(new Teleport(this->texture_mgr));
                break;
            case WeaponID::WNone:
                this->weapon = std::shared_ptr<Weapon>(new WeaponNone(this->texture_mgr));
                break;
            case WeaponID::WExplode:
                break;
            case WeaponID::WFragment:
                break;
        }
    }
}

const Worm::WeaponID &Worm::Worm::getWeaponID() const {
    return this->weapon->getWeaponID();
}

void Worm::Worm::setWeaponAngle(float angle) {
    this->weapon->setAngle(angle, this->direction);
}

void Worm::Worm::setPosition(GUI::Position p) {
    this->position = p;
}

void Worm::Worm::startShot() {
    if (!this->hasFired) {
        this->weapon->startShot();
    }
}

void Worm::Worm::endShot() {
    if (this->weapon->getWeaponID() != WeaponID::WAerial &&
        this->weapon->getWeaponID() != WeaponID::WTeleport &&
        this->weapon->getWeaponID() != WeaponID::WNone) {
        if (!this->hasFired) {
            this->weapon->endShot();
            this->playWeaponSoundEffect(this->getWeaponID());
            this->hasFired = true;
        }
    }
}

void Worm::Worm::mouseButtonDown(GUI::Position position, IO::Stream<IO::PlayerMsg> *out) {
    IO::PlayerInput i = this->state->positionSelected(*this);
    if (i != IO::PlayerInput::moveNone && !this->hasFired && this->weapon->positionSelected()) {
        this->playWeaponSoundEffect(this->weapon->getWeaponID());
        IO::PlayerMsg msg;
        msg.input = i;
        msg.position = position;
        *out << msg;
    }
}

void Worm::Worm::playWeaponSoundEffect(const WeaponID &id) {
    this->soundEffectPlayer = nullptr;

    switch (id) {
        case WeaponID::WBazooka:
            this->soundEffectPlayer =
                std::shared_ptr<GUI::SoundEffectPlayer>(new GUI::SoundEffectPlayer{
                    this->sound_effect_mgr.get(GUI::GameSoundEffects::Shot), true});
            this->soundEffectPlayer->play();
            break;
        case WeaponID::WGrenade:
            this->soundEffectPlayer =
                std::shared_ptr<GUI::SoundEffectPlayer>(new GUI::SoundEffectPlayer{
                    this->sound_effect_mgr.get(GUI::GameSoundEffects::Shot), true});
            this->soundEffectPlayer->play();
            break;
        case WeaponID::WCluster:
            this->soundEffectPlayer =
                std::shared_ptr<GUI::SoundEffectPlayer>(new GUI::SoundEffectPlayer{
                    this->sound_effect_mgr.get(GUI::GameSoundEffects::Shot), true});
            this->soundEffectPlayer->play();
            break;
        case WeaponID::WMortar:
            this->soundEffectPlayer =
                std::shared_ptr<GUI::SoundEffectPlayer>(new GUI::SoundEffectPlayer{
                    this->sound_effect_mgr.get(GUI::GameSoundEffects::Shot), true});
            this->soundEffectPlayer->play();
            break;
        case WeaponID::WBanana:
            this->soundEffectPlayer =
                std::shared_ptr<GUI::SoundEffectPlayer>(new GUI::SoundEffectPlayer{
                    this->sound_effect_mgr.get(GUI::GameSoundEffects::Shot), true});
            this->soundEffectPlayer->play();
            break;
        case WeaponID::WHoly:
            this->soundEffectPlayer =
                std::shared_ptr<GUI::SoundEffectPlayer>(new GUI::SoundEffectPlayer{
                    this->sound_effect_mgr.get(GUI::GameSoundEffects::Holy), true});
            this->soundEffectPlayer->play();
            break;
        case WeaponID::WAerial:
            this->soundEffectPlayer =
                std::shared_ptr<GUI::SoundEffectPlayer>(new GUI::SoundEffectPlayer{
                    this->sound_effect_mgr.get(GUI::GameSoundEffects::AirStrike), true});
            this->soundEffectPlayer->play();
            break;
        case WeaponID::WDynamite:
            break;
        case WeaponID::WBaseballBat:
            break;
        case WeaponID::WTeleport:
            break;
        case WeaponID::WNone:
            break;
        case WeaponID::WExplode:
            break;
        case WeaponID::WFragment:
            break;
    }
}

void Worm::Worm::reset() {
    this->hasFired = false;
}
