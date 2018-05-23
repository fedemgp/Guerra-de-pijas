//
// Created by rodrigo on 21/05/18.
//

#include <iostream>
#include "PlayerBazooka.h"
#include "Player.h"
/*
 * TODO add previous and finish states of bazooka, using wbazbak.png and wbazink.png
 */
Worms::Bazooka::Bazooka() : State(Worm::StateID::Bazooka) {}

void Worms::Bazooka::update(Worms::Player &p, float dt, b2Body *body){

}

void Worms::Bazooka::moveRight(Worms::Player &p) {
    p.setState(Worm::StateID::Walk);
    p.direction = Direction::right;
}

void Worms::Bazooka::moveLeft(Worms::Player &p) {
    p.setState(Worm::StateID::Walk);
    p.direction = Direction::left;
}

void Worms::Bazooka::jump(Worms::Player &p) {}

void Worms::Bazooka::stopMove(Worms::Player &p) {}

void Worms::Bazooka::bazooka(Worms::Player &p) {}

void Worms::Bazooka::pointUp(Worms::Player &p){
    p.increaseAngle();
    std::cout << "increase angle " << p.getAngle() << std::endl;
}

void Worms::Bazooka::pointDown(Worms::Player &p){
    p.decreaseAngle();
    std::cout << "decrease angle " << p.getAngle() << std::endl;
}
