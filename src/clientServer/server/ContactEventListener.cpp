/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 20/05/18
 */

#include <iostream>
#include "ContactEventListener.h"
#include "Player.h"

void ContactEventListener::BeginContact(b2Contact *contact){
    Worms::Entity *playerA = static_cast<Worms::Entity*>(contact->GetFixtureA()->GetBody()->GetUserData());
    Worms::Entity *playerB = static_cast<Worms::Entity*>(contact->GetFixtureB()->GetBody()->GetUserData());
    /*
     * If fixture A is a Worm, then call startContact. This will delegate
     * the action to the internal state. For example, when a worm jump,
     * it start with a state startJump, after a few seconds (so the clients
     * could animate the impulse the worm takes to jump), it changes its
     * state to Jumping. The moment the state changes to endJump will be
     * when box2d detects a collision between the worm and the girder.
     */
    if (playerA){
        switch (playerA->getEntityId()){
            case Worms::EntityID::EtWorm:
                dynamic_cast<Worms::Player*>(playerA)->startContact();
                break;
            case Worms::EntityID::EtBullet:
                dynamic_cast<Worms::Bullet*>(playerA)->startContact();
                break;
        }
    }
    if (playerB){
        switch (playerB->getEntityId()){
            case Worms::EntityID::EtWorm:
                dynamic_cast<Worms::Player*>(playerB)->startContact();
                break;
            case Worms::EntityID::EtBullet:
                dynamic_cast<Worms::Bullet*>(playerB)->startContact();
                break;
        }
    }
}

void ContactEventListener::EndContact(b2Contact *contact){
    Worms::Entity *playerA = static_cast<Worms::Entity*>(contact->GetFixtureA()->GetBody()->GetUserData());
    Worms::Entity *playerB = static_cast<Worms::Entity*>(contact->GetFixtureB()->GetBody()->GetUserData());

    if (playerA){
        switch (playerA->getEntityId()){
            case Worms::EntityID::EtWorm:
                dynamic_cast<Worms::Player*>(playerA)->endContact();
                break;
            case Worms::EntityID::EtBullet:
                dynamic_cast<Worms::Bullet*>(playerA)->endContact();
                break;
        }
    }
    if (playerB){
        switch (playerB->getEntityId()){
            case Worms::EntityID::EtWorm:
                dynamic_cast<Worms::Player*>(playerB)->endContact();
                break;
            case Worms::EntityID::EtBullet:
                dynamic_cast<Worms::Bullet*>(playerB)->endContact();
                break;
        }
    }
}
