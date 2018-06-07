/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 06/06/18
 */

#include "Subject.h"

void Subject::addObserver(Observer *obs) {
    this->observers.emplace(obs);
}
// TODO check possibly raceCondition
void Subject::removeObserver(Observer *obs) {
    this->observers.erase(this->observers.find(obs));
}

void Subject::notify(const Worms::PhysicsEntity &entity, Event event) {
    for (auto &observer : this->observers) {
        observer->onNotify(entity, event);
    }
}
