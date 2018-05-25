/*
 *  Created by Rodrigo.
 *  date: 20/05/18
 */


#include "PlayerStartBackFlip.h"

Worms::StartBackFlip::StartBackFlip() : State(Worm::StateID::StartBackFlip) {}

void Worms::StartBackFlip::update(Worms::Player &p, float dt, b2Body *body) {
    this->timeElapsed += dt;
    if (this->timeElapsed >= START_BACKFLIP_TIME) {
        float32 mass = body->GetMass();
        b2Vec2 impulses = {mass * BACKFLIP_VEL_X, mass * BACKFLIP_VEL_Y};
        if (p.direction == Direction::left){
            impulses.x *= -1;
        }
        p.setState(Worm::StateID::BackFlipping);
        /*
         * When the worm jumps, it needs an initial impulse in the y axis
         * that will never will be applied again. In the x axis, the worms
         * moves in RUM, so it needs an initial impulse (because his friction
         * coeficient is 0) and then needs an end impulse, of equal absolute
         * value and different sign.
         */
        body->ApplyLinearImpulse(impulses, body->GetWorldCenter(), true);
    }
}

void Worms::StartBackFlip::moveRight(Worms::Player &p) {}

void Worms::StartBackFlip::moveLeft(Worms::Player &p) {}

void Worms::StartBackFlip::jump(Worms::Player &p) {}

void Worms::StartBackFlip::backFlip(Worms::Player &p) {}

void Worms::StartBackFlip::stopMove(Worms::Player &p) {}

void Worms::StartBackFlip::bazooka(Worms::Player &p) {}

void Worms::StartBackFlip::pointUp(Worms::Player &p){}

void Worms::StartBackFlip::pointDown(Worms::Player &p){}
