/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 18/05/18
 */

#ifndef __GUIGame_H__
#define __GUIGame_H__

#include "Animation.h"
#include "GameStateMsg.h"
#include "Stream.h"
#include "Window.h"
#include "Worm.h"

namespace GUI {
class Game {
   public:
    Game(Window &w);
    ~Game();
    void start(IO::Stream<IO::GameStateMsg> *input, IO::Stream<IO::PlayerInput> *output);
    void update(float dt);
    void render();

   private:
    Window &window;
    Worm::Worm worm;
    int x{0}, y{0};
};
}

#endif  //__GUIGame_H__
