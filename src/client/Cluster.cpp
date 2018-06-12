/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 04/06/18
 */

#include <cmath>

#include "Cluster.h"

Worm::Cluster::Cluster(const GUI::GameTextureManager &tex)
    : Weapon(tex, GUI::GameTextures::WormCluster, CLUSTER_CENTER_FRAME, WeaponID::WCluster),
      scope(this->textureMgr),
      powerBar(this->textureMgr) {}

void Worm::Cluster::update(float dt) {
    this->weaponAnimation.update(dt);
    this->scope.update(dt);
    this->powerBar.update(dt);
}

void Worm::Cluster::render(GUI::Position &p, GUI::Camera &cam, SDL_RendererFlip &flip) {
    this->weaponAnimation.render(p, cam, flip);
    this->scope.render(p, cam, flip);
    this->powerBar.render(p, cam, flip);
}

void Worm::Cluster::setAngle(float angle, Worm::Direction d) {
    this->weaponAnimation.setFrame((int)std::ceil(angle / ANGLE_STEP) + this->centerFrame);
    this->scope.setAngle(angle, d);
    this->powerBar.setAngle(angle, d);
}

void Worm::Cluster::startShot() {
    this->powerBar.startShot();
}

void Worm::Cluster::endShot() {
    this->powerBar.endShot();
}
