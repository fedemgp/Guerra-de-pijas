/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 20/05/18
 */

#include <iostream>

#include "ContactEventListener.h"
#include "Player.h"

/**
 * @brief Pre collision solver handler for Box2D. Notifies colliding objects so the can act
 * appropriately.
 *
 * @param contact Collision contact.
 * @param oldManifold Manifold.
 */
void ContactEventListener::PreSolve(b2Contact *contact, const b2Manifold *oldManifold) {
    Worms::PhysicsEntity *e1 =
        static_cast<Worms::PhysicsEntity *>(contact->GetFixtureA()->GetBody()->GetUserData());
    Worms::PhysicsEntity *e2 =
        static_cast<Worms::PhysicsEntity *>(contact->GetFixtureB()->GetBody()->GetUserData());

    if (!e1 || !e2) {
        return;
    }

    e1->contactWith(*e2, *contact);
    e2->contactWith(*e1, *contact);
}

void ContactEventListener::BeginContact(b2Contact *contact) {
    Worms::PhysicsEntity *playerA =
        static_cast<Worms::PhysicsEntity *>(contact->GetFixtureA()->GetBody()->GetUserData());
    Worms::PhysicsEntity *playerB =
        static_cast<Worms::PhysicsEntity *>(contact->GetFixtureB()->GetBody()->GetUserData());
    /*
     * If fixture A is a Worm, then call startContact. This will delegate
     * the action to the internal state. For example, when a worm jump,
     * it run with a state startJump, after a few seconds (so the clients
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

    void *fixtureData = contact->GetFixtureA()->GetUserData();
    if (fixtureData) {
        Worms::PhysicsEntity *sensor = static_cast<Worms::TouchSensor *>(fixtureData);
        sensor->startContact(playerB, *contact);
    }

    fixtureData = contact->GetFixtureB()->GetUserData();
    if (fixtureData) {
        Worms::PhysicsEntity *sensor = static_cast<Worms::TouchSensor *>(fixtureData);
        sensor->startContact(playerA, *contact);
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

    void *fixtureData = contact->GetFixtureA()->GetUserData();
    if (fixtureData) {
        Worms::PhysicsEntity *sensor = static_cast<Worms::TouchSensor *>(fixtureData);
        sensor->endContact(playerB, *contact);
    }

    fixtureData = contact->GetFixtureB()->GetUserData();
    if (fixtureData) {
        Worms::PhysicsEntity *sensor = static_cast<Worms::TouchSensor *>(fixtureData);
        sensor->endContact(playerA, *contact);
    }
}
