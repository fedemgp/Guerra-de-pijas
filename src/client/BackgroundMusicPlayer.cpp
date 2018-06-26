//
// Created by rodrigo on 25/06/18.
//

#include "BackgroundMusicPlayer.h"

GUI::BackgroundMusicPlayer::BackgroundMusicPlayer(const GUI::BackgroundMusic &backgroundMusic)
        : backgroundMusic(&backgroundMusic) {}

GUI::BackgroundMusicPlayer::~BackgroundMusicPlayer() {}

void GUI::BackgroundMusicPlayer::play() {
    this->backgroundMusic->play();
}
