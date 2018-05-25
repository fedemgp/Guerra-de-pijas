/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 18/05/18
 */

#ifndef __GUIGame_H__
#define __GUIGame_H__

#include <vector>
#include "Animation.h"
#include "GameStateMsg.h"
#include "GameTextures.h"
#include "../server/Stage.h"
#include "Stream.h"
#include "TextureManager.h"
#include "Window.h"
#include "Worm.h"

namespace GUI {
class Game {
   public:
    Game(Window &w, Worms::Stage &&stage);
    ~Game();
    void start(IO::Stream<IO::GameStateMsg> *serverResponse,
               IO::Stream<IO::PlayerInput> *clientResponse);
    void update(float dt);
    void render();

   private:
    Window &window;
    GameTextureManager texture_mgr;
    std::vector<Worm::Worm> worms;
    Worms::Stage stage;
    float x{0}, y{0};
    float camx{0}, camy{0};
    float scale{15.0f};  // pixels per meter
};
}  // namespace GUI

#endif  //__GUIGame_H__
