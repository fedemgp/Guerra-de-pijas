/*
 *  Created by Rodrigo.
 *  date: 21/05/18
 */

#include "PlayerBackFlipping.h"
#include "Player.h"

Worms::BackFlipping::BackFlipping() : State(Worm::StateID::BackFlipping) {}

void Worms::BackFlipping::update(Worms::Player &p, float dt, b2Body *body) {
    /*
     * when the worm lands (there was a collision between the worm and the
     * girder) it has to changes its state to endJump, and take an impulse
     * of equal absolute value and different sign of the impulse taken in
     * startJump stage (remember, the worm has a friction coefficient 0).
     *
     * In the y-axis there will be no impulse because its velocity was
     * cancelled because of the collision with the girder.
     */
    if (p.getContactCount() > 0) {
        float32 mass = body->GetMass();
        b2Vec2 previousVel = body->GetLinearVelocity();
        b2Vec2 impulses = {mass * (0.0f - previousVel.x), 0.0f};
        body->ApplyLinearImpulseToCenter(impulses, true);

        p.setState(Worm::StateID::EndBackFlip);
    }
}

void Worms::BackFlipping::moveRight(Worms::Player &p) {}

void Worms::BackFlipping::moveLeft(Worms::Player &p) {}

void Worms::BackFlipping::jump(Worms::Player &p) {}

void Worms::BackFlipping::stopMove(Worms::Player &p) {}

void Worms::BackFlipping::backFlip(Worms::Player &p) {}

void Worms::BackFlipping::bazooka(Worms::Player &p) {}

void Worms::BackFlipping::pointUp(Worms::Player &p) {}

void Worms::BackFlipping::pointDown(Worms::Player &p) {}

void Worms::BackFlipping::startShot(Worms::Player &p) {}

void Worms::BackFlipping::endShot(Worms::Player &p) {}
