/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 10/06/18
 */

#include <sstream>

#include "Armory.h"

GUI::Armory::Armory(const GUI::GameTextureManager &textureManager, GUI::Camera &cam,
                    GUI::Font &font)
    : manager(textureManager), camera(cam), font(font), weaponButton(font) {}

void GUI::Armory::render() {
    const Texture *temp = this->weaponIcons.back();
    ScreenPosition iconPos{-temp->getWidth() / 2, temp->getHeight() / 2};
    ScreenPosition textPos{-temp->getWidth() / 2, temp->getHeight() * 3 / 2};
    int i = 1;
    for (auto &weapon : this->weaponIcons) {
        iconPos.x += weapon->getWidth();
        textPos.x += weapon->getWidth();

        std::ostringstream button;
        button << BUTTON_ROOT_STR << i++;

        weaponButton.set(button.str(), SDL_Color{0, 0, 0}, 25);
        weaponButton.renderFixed(textPos, this->camera);
        this->camera.drawLocal(*weapon, iconPos);
    }
}

void GUI::Armory::loadWeapons() {
    this->weaponIcons.emplace_back(&this->manager.get(GUI::GameTextures::BazookaIcon));
    this->weaponIcons.emplace_back(&this->manager.get(GUI::GameTextures::GrenadeIcon));
    this->weaponIcons.emplace_back(&this->manager.get(GUI::GameTextures::ClusterIcon));
    this->weaponIcons.emplace_back(&this->manager.get(GUI::GameTextures::MortarIcon));
    this->weaponIcons.emplace_back(&this->manager.get(GUI::GameTextures::BananaIcon));
    this->weaponIcons.emplace_back(&this->manager.get(GUI::GameTextures::HolyIcon));
    this->weaponIcons.emplace_back(&this->manager.get(GUI::GameTextures::AirIcon));
    this->weaponIcons.emplace_back(&this->manager.get(GUI::GameTextures::DynamiteIcon));
    this->weaponIcons.emplace_back(&this->manager.get(GUI::GameTextures::BaseballBatIcon));
    this->weaponIcons.emplace_back(&this->manager.get(GUI::GameTextures::TeleportIcon));
}
