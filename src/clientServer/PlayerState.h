#ifndef _PLAYERSTATE_H
#define _PLAYERSTATE_H


namespace Worms {
    class Player;
    class State {
    public:
        virtual ~State() = default;
        virtual float update() = 0;
        virtual void moveRight(Player &p) = 0;
        virtual void moveLeft(Player &p) = 0;
        virtual void stopMove(Player &p) = 0;
    };
}

#endif //_PLAYERSTATE_H
