/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 06/06/18
 */

#ifndef __OBSERVER_H__
#define __OBSERVER_H__

enum class Event {
    Explode,
    OnExplode,
    Shot,
    Drowning,
    Drowned,
    EndTurn,
    Hit,
    EndHit,
    NewWormToFollow,
    ImpactEnd,
    TurnEnded,
    WormFalling,
    WormLanded,
    Dead,
    Dying,
    DamageOnLanding,
    NextTurn,
    Teleported,
    P2PWeaponUsed,
    StartGame,
    NewPlayer,
    EndGame,
    CreateGame,
    JoinGame
};

class Subject;

class Observer {
   public:
    virtual ~Observer() = default;
    virtual void onNotify(Subject &subject, Event event) = 0;
};

#endif  //__OBSERVER_H__
