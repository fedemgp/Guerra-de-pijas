/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 18/05/18
 */

#include "Physics.h"

Worms::Physics::Physics(b2Vec2 gravity)
        : gravity(gravity), world(this->gravity), contactEventListener(new ContactEventListener) {
    this->world.SetContactListener(this->contactEventListener.get());
}

/**
 * @brief Updates the physics engine.
 *
 * @param dt Seconds elapsed since last call to this function.
 */
void Worms::Physics::update(float dt) {
    this->world.Step(dt, this->vIterations, this->pIterations);
}

/**
 * @brief Creates a new physical body.
 *
 * @param bodyDef Body definition.
 * @return new body.
 */
b2Body* Worms::Physics::createBody(b2BodyDef& bodyDef) {
    return this->world.CreateBody(&bodyDef);
}
