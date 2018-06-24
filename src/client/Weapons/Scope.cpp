/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 04/06/18
 */

#include "Scope.h"
#include "Direction.h"
#include "Weapon.h"

Weapon::Scope::Scope(const GUI::GameTextureManager &tex)
    : animation(tex.get(GUI::GameTextures::Scope), false, 0, false) {}

void Weapon::Scope::setAngle(float angle, Worm::Direction d) {
    this->angle = d == Worm::Direction::right ? angle : 180 - angle;
}

void Weapon::Scope::update(float dt) {
    this->animation.update(dt);
}

void Weapon::Scope::render(GUI::Position &p, GUI::Camera &cam, SDL_RendererFlip &flip) {
    GUI::Position scopePos = GUI::Position(SCOPE_DISTANCE * cos(this->angle * PI / 180),
                                           SCOPE_DISTANCE * sin(this->angle * PI / 180)) +
                             p;
    this->animation.render(scopePos, cam, flip);
}
