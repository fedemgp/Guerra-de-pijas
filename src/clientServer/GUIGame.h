/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 18/05/18
 */

#ifndef __GUIGame_H__
#define __GUIGame_H__

#include "Animation.h"

namespace GUI{
    class GUIGame{
    public:
        GUIGame(Window &w);
        ~GUIGame();
        void start(IO::Stream<IO::GameStateMsg> *input, IO::Stream<IO::PlayerInput> *output);
        void update(float dt);
        void render();

    private:
        Window &window;
        Animation wwalk;
        int x{0}, y{0};
    };
}


#endif //__GUIGame_H__
