/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 20/05/18
 */

#include <iostream>

#include "ContactEventListener.h"
#include "Player.h"

void ContactEventListener::BeginContact(b2Contact *contact) {
    Worms::PhysicsEntity *playerA =
        static_cast<Worms::PhysicsEntity *>(contact->GetFixtureA()->GetBody()->GetUserData());
    Worms::PhysicsEntity *playerB =
        static_cast<Worms::PhysicsEntity *>(contact->GetFixtureB()->GetBody()->GetUserData());
    /*
     * If fixture A is a Worm, then call startContact. This will delegate
     * the action to the internal state. For example, when a worm jump,
     * it start with a state startJump, after a few seconds (so the clients
     * could animate the impulse the worm takes to jump), it changes its
     * state to Jumping. The moment the state changes to endJump will be
     * when box2d detects a collision between the worm and the girder.
     */
    if (playerA) {
        playerA->startContact(playerB);
    }
    if (playerB) {
        playerB->startContact(playerA);
    }
}

void ContactEventListener::EndContact(b2Contact *contact) {
    Worms::PhysicsEntity *playerA =
        static_cast<Worms::PhysicsEntity *>(contact->GetFixtureA()->GetBody()->GetUserData());
    Worms::PhysicsEntity *playerB =
        static_cast<Worms::PhysicsEntity *>(contact->GetFixtureB()->GetBody()->GetUserData());

    if (playerA) {
        playerA->endContact(playerB);
    }
    if (playerB) {
        playerB->endContact(playerA);
    }
}
