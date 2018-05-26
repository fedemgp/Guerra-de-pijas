/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 18/05/18
 */

#include "Stage.h"
#include "Point.h"

Worms::Stage::Stage() {
    this->playerPositions.emplace_back(Math::Point<float>{0.0f, 20.0f});
    this->playerPositions.emplace_back(Math::Point<float>{-3.0f, 20.0f});
    this->playerPositions.emplace_back(Math::Point<float>{-8.0f, 15.0f});

    this->girderPositions.emplace_back(Math::Point<float>{0.0f, 13.0f});
    this->girderPositions.emplace_back(Math::Point<float>{-5.0f, 10.0f});
    this->girderPositions.emplace_back(Math::Point<float>{-17.0f, 0.0f});
    this->girderPositions.emplace_back(Math::Point<float>{-11.0f, 5.0f});
    this->girderPositions.emplace_back(Math::Point<float>{-3.0f, 0.0f});
    this->girderPositions.emplace_back(Math::Point<float>{5.0f, 0.0f});
    this->girderPositions.emplace_back(Math::Point<float>{11.0f, 0.0f});
}

const std::vector<Math::Point<float>>& Worms::Stage::getWormPositions() const {
    return this->playerPositions;
}

const std::vector<Math::Point<float>>& Worms::Stage::getGirderPositions() const {
    return this->girderPositions;
}

float Worms::Stage::getHeight() const {
    return this->height;
}

float Worms::Stage::getWidth() const {
    return this->width;
}
