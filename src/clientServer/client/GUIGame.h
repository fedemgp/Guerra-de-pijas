/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 18/05/18
 */

#ifndef __GUIGame_H__
#define __GUIGame_H__

#include <list>
#include <vector>

#include "../server/Stage.h"  //TODO check this
#include "Animation.h"
#include "Bullet.h"
#include "Camera.h"
#include "Explosion.h"
#include "Font.h"
#include "GameStateMsg.h"
#include "GameTextures.h"
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
    void render_controls();
    void renderBackground();

    float scale{13.0f};  // pixels per meter
    Window &window;
    GameTextureManager texture_mgr;
    std::vector<Worm::Worm> worms;
    Worms::Stage stage;
    std::list<std::shared_ptr<Ammo::Bullet>> bullets;
    IO::GameStateMsg snapshot{0};
    Camera cam;
    Font font;
    SDL_Color backgroundColor{0xba, 0x8d, 0xc6};
    std::vector<SDL_Color> teamColors;
};
}  // namespace GUI

#endif  //__GUIGame_H__
