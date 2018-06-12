/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 18/05/18
 */

#include "Stage.h"
#include "Point.h"

Worms::Stage::Stage() {
    uint16_t health = 100;
    this->players.push_back(Worms::WormData{health, Math::Point<float>{50.0f, 20.0f}});
    this->players.push_back(Worms::WormData{health, Math::Point<float>{-3.0f, 20.0f}});
    this->players.push_back(Worms::WormData{health, Math::Point<float>{-5.0f, 20.0f}});

    this->girders.push_back(Girder{11, 1.42f, Math::Point<float>{50.0f, 10.0f}});
    this->girders.push_back(Girder{31, 1.42f, Math::Point<float>{-50.0f, 7.0f}});
    this->girders.push_back(Girder{20, 1.42f, Math::Point<float>{-30.0f, 10.0f}});
    this->girders.push_back(Girder{10, 1.42f, Math::Point<float>{0.0f, 13.0f}});
    this->girders.push_back(Girder{4, 1.42f, Math::Point<float>{-5.0f, 9.5f}});
    this->girders.push_back(Girder{8, 1.42f, Math::Point<float>{-17.0f, 2.0f}});
    this->girders.push_back(Girder{14, 1.42f, Math::Point<float>{-11.0f, 5.0f}});
    this->girders.push_back(Girder{2.5f, 1.42f, Math::Point<float>{-3.0f, 2.0f}});
    this->girders.push_back(Girder{7, 1.42f, Math::Point<float>{5.0f, 2.0f}});
    this->girders.push_back(Girder{13.4f, 1.42f, Math::Point<float>{30.0f, 15.0f}});
    this->girders.push_back(Girder{13.4f, 1.42f, Math::Point<float>{11.0f, 2.0f}});
}

const std::vector<Worms::WormData>& Worms::Stage::getWorms() const {
    return this->players;
}

const std::vector<Worms::Girder>& Worms::Stage::getGirders() const {
    return this->girders;
}

float Worms::Stage::getHeight() const {
    return this->height;
}

float Worms::Stage::getWidth() const {
    return this->width;
}
