/*
 *  Created by Rodrigo.
 *  date: 21/05/18
 */


#include "PlayerEndBackFlip.h"
#include "PlayerState.h"
#include "Player.h"

Worms::EndBackFlip::EndBackFlip(): State(Worm::StateID::EndBackFlip){}

void Worms::EndBackFlip::update(Worms::Player &p, float dt, b2Body *body){
    this->timeElapsed += dt;
    if (this->timeElapsed > BACK_FLIP_LAND_TIME){
        p.setState(Worm::StateID::Still);
    }
}

void Worms::EndBackFlip::moveRight(Worms::Player &p){}

void Worms::EndBackFlip::moveLeft(Worms::Player &p){}

void Worms::EndBackFlip::jump(Worms::Player &p){}

void Worms::EndBackFlip::stopMove(Worms::Player &p){}

void Worms::EndBackFlip::backFlip(Worms::Player &p) {}
