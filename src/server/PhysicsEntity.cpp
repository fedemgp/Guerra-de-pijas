/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 26/05/18
 */

#include "PhysicsEntity.h"

Worms::PhysicsEntity::PhysicsEntity(Worms::EntityID id) : id(id) {}

Worms::EntityID Worms::PhysicsEntity::getEntityId() {
    return this->id;
}

Worms::PhysicsEntity::PhysicsEntity(Worms::PhysicsEntity &&other){
    this->id = other.id;
    this->handlingContact = other.handlingContact;

    other.handlingContact = false;
}
