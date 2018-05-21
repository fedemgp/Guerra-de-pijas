/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 20/05/18
 */

#include "ContactEventListener.h"
#include "Player.h"

void ContactEventListener::BeginContact(b2Contact *contact){
    void *player = contact->GetFixtureA()->GetBody()->GetUserData();
    /*
     * If fixture A is a Worm, then call startContact. This will delegate
     * the action to the internal state. For example, when a worm jump,
     * it start with a state startJump, after a few seconds (so the clients
     * could animate the impulse the worm takes to jump), it changes its
     * state to Jumping. The moment the state changes to endJump will be
     * when box2d detects a collision between the worm and the girder.
     */
    if (player){
        static_cast<Worms::Player*>(player)->startContact();
    }

    player = contact->GetFixtureB()->GetBody()->GetUserData();
    if (player){
        static_cast<Worms::Player*>(player)->startContact();
    }
}

void ContactEventListener::EndContact(b2Contact *contact){
    void *player = contact->GetFixtureA()->GetBody()->GetUserData();
    if (player){
        static_cast<Worms::Player*>(player)->endContact();
    }

    player = contact->GetFixtureB()->GetBody()->GetUserData();
    if (player){
        static_cast<Worms::Player*>(player)->endContact();
    }
}
