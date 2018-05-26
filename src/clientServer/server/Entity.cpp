/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 26/05/18
 */

#include "Entity.h"

Worms::Entity::Entity(Worms::EntityID id): id(id){}

Worms::EntityID Worms::Entity::getEntityId(){
    return this->id;
}


