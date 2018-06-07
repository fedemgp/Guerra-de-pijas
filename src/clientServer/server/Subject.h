/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 06/06/18
 */

#ifndef __Subject_H__
#define __Subject_H__

#include <set>

#include "Observer.h"

class Subject {
   public:
    void addObserver(Observer *obs);
    void removeObserver(Observer *obs);

   protected:
    /**
     * Notify all observers with the Event id, so the Observer can do
     * what is necessary
     * @param entity
     * @param event
     */
    void notify(const Worms::PhysicsEntity &entity, Event event);

   private:
    std::set<Observer *> observers;
    int numObservers;
};

#endif  //__Subject_H__
