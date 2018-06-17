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

    this->girders.push_back(GirderData{11, 1.42f, 0.0f, Math::Point<float>{50.0f, 10.0f}});
    this->girders.push_back(GirderData{31, 1.42f, 0.0f, Math::Point<float>{-50.0f, 7.0f}});
    this->girders.push_back(GirderData{20, 1.42f, 0.0f, Math::Point<float>{-30.0f, 10.0f}});
    this->girders.push_back(GirderData{10, 1.42f, 0.0f, Math::Point<float>{0.0f, 13.0f}});
    this->girders.push_back(GirderData{4, 1.42f, 0.0f, Math::Point<float>{-5.0f, 9.5f}});
    this->girders.push_back(GirderData{8, 1.42f, 0.0f, Math::Point<float>{-17.0f, 2.0f}});
    this->girders.push_back(GirderData{14, 1.42f, 0.0f, Math::Point<float>{-11.0f, 5.0f}});
    this->girders.push_back(GirderData{2.5f, 1.42f, 0.0f, Math::Point<float>{-3.0f, 2.0f}});
    this->girders.push_back(GirderData{7, 1.42f, 0.0f, Math::Point<float>{5.0f, 2.0f}});
    this->girders.push_back(GirderData{13.4f, 1.42f, 0.0f, Math::Point<float>{30.0f, 15.0f}});
    this->girders.push_back(GirderData{13.4f, 1.42f, 0.0f, Math::Point<float>{11.0f, 2.0f}});
    this->girders.push_back(GirderData{4.0f, 1.42f, -45.0f, Math::Point<float>{15.0f, 10.0f}});
    this->girders.push_back(GirderData{8.0f, 1.42f, -30.0f, Math::Point<float>{40.0f, 13.0f}});
    this->girders.push_back(GirderData{8.0f, 1.42f, -46.0f, Math::Point<float>{7.5f, 11.0f}});
    this->girders.push_back(GirderData{10.0f, 1.42f, -60.0f, Math::Point<float>{57.0f, 6.0f}});
    this->girders.push_back(GirderData{10.0f, 1.42f, -46.0f, Math::Point<float>{61.5f, 0.0f}});
}

const std::vector<Worms::WormData>& Worms::Stage::getWorms() const {
    return this->players;
}

const std::vector<Worms::GirderData>& Worms::Stage::getGirders() const {
    return this->girders;
}

float Worms::Stage::getHeight() const {
    return this->height;
}

float Worms::Stage::getWidth() const {
    return this->width;
}
