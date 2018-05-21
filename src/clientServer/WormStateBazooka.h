/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 20/05/18
 */

#ifndef __WormStateBazooka_H__
#define __WormStateBazooka_H__

#include "WormState.h"

namespace Worm{
    class Bazooka: State{
    public:
        Bazooka();
        ~Bazooka();
        virtual void update(float dt) override;
        virtual IO::PlayerInput moveRight(Worm &w) override;
        virtual IO::PlayerInput moveLeft(Worm &w) override;
        virtual IO::PlayerInput stopMove(Worm &w) override;
        virtual IO::PlayerInput jump(Worm &w) override;
        virtual IO::PlayerInput bazooka(Worm &w) override;
    };
}


#endif //__WormStateBazooka_H__
