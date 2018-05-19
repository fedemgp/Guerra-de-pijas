/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 18/05/18
 */

#ifndef __GUIGame_H__
#define __GUIGame_H__

#include <vector>
#include "Animation.h"
#include "GameStateMsg.h"
#include "Stream.h"
#include "TextureManager.h"
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
    Worm::TextureManager texture_mgr;
    std::vector<Worm::Worm> worms;
    int x{0}, y{0};
};
}  // namespace GUI

#endif  //__GUIGame_H__
