/*
 *  Created by Rodrigo.
 *  date: 28/05/18
 */


#include "Hit.h"
#include "Player.h"

Worms::Hit::Hit() : State(Worm::StateID::Hit) {}

void Worms::Hit::update(Worms::Player &p, float dt, b2Body *body) {
    /*
     * when the worm lands (there was a collision between the worm and the
     * girder) it has to change its state to still, and take an impulse
     * of equal absolute value and different sign of the impulse taken in
     * hit stage (remember, the worm has a friction coefficient 0).
     *
     * In the y-axis there will be no impulse because its velocity was
     * cancelled because of the collision with the girder.
     */
    if (p.getContactCount() > 0) {
        float32 mass = body->GetMass();
        b2Vec2 previousVel = body->GetLinearVelocity();
        b2Vec2 impulses = {mass * (0.0f - previousVel.x), 0.0f};
        body->ApplyLinearImpulseToCenter(impulses, true);

        p.setState(Worm::StateID::Still);
    }
}

void Worms::Hit::moveRight(Worms::Player &p) {}

void Worms::Hit::moveLeft(Worms::Player &p) {}

void Worms::Hit::jump(Worms::Player &p) {}

void Worms::Hit::stopMove(Worms::Player &p) {}

void Worms::Hit::backFlip(Worms::Player &p) {}

void Worms::Hit::bazooka(Worms::Player &p) {}

void Worms::Hit::pointUp(Worms::Player &p) {}

void Worms::Hit::pointDown(Worms::Player &p) {}

void Worms::Hit::startShot(Worms::Player &p) {}

void Worms::Hit::endShot(Worms::Player &p) {}
