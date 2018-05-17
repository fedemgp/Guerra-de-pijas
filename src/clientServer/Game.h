/*
 * Created by Federico Manuel Gomez Peter 
 * Date: 17/05/18.
 */

#ifndef __GAME_H__
#define __GAME_H__

#include "Animation.h"
#include "GameStateMsg.h"
#include "Stream.h"
#include "Window.h"

namespace GUI {class Game {
    public:
        Game(Window &w);
        ~Game();
        void start(IO::Stream<IO::GameStateMsg> *input, IO::Stream<IO::PlayerInput> *output);
        void update(float dt);
        void render();

    private:
        Window &window;
        Animation wwalk;
        int x{0}, y{0};
    };
}  // namespace GUI


#endif //__GAME_H__
