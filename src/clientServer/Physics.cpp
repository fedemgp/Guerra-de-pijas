/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 18/05/18
 */

#include "Physics.h"

Worms::Physics::Physics(b2Vec2 gravity) : gravity(gravity), world(this->gravity) {}

void Worms::Physics::update(float dt) {
    this->world.Step(dt, this->vIterations, this->pIterations);
}
// TODO, separate this on createWorm and createBullet
b2Body* Worms::Physics::createBody(b2BodyDef& bodyDef) {
    return this->world.CreateBody(&bodyDef);
}