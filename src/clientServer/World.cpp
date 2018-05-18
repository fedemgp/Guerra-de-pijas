/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 18/05/18
 */

#include "World.h"
#include "Point.h"

Worms::World::World() {
    this->playerPositions.emplace_back(Math::Point<float>{0.0f, 15.0f});
}

const std::vector<Math::Point<float>>& Worms::World::getWormPosition() const {
    return this->playerPositions;
}

float Worms::World::getHeight() const {
    return this->height;
}

float Worms::World::getWidth() const {
    return this->width;
}