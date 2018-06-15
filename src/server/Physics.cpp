/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 18/05/18
 */

#include "Physics.h"

Worms::Physics::Physics(b2Vec2 gravity, float timeStep)
    : timeStep(timeStep),
      gravity(gravity),
      world(this->gravity),
      contactEventListener(new ContactEventListener) {
    this->world.SetContactListener(this->contactEventListener.get());
}

/**
 * @brief Updates the physics engine.
 *
 * @param dt Seconds elapsed since last call to this function.
 */
void Worms::Physics::update(float dt) {
    this->accumTime += dt;

    /* updates the physics engine */
    for (int i = 0; i < 5 && this->accumTime > this->timeStep; i++) {
        this->world.Step(this->timeStep, this->vIterations, this->pIterations);
        this->accumTime -= this->timeStep;
    }
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
