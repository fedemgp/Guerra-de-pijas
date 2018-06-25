#ifndef JOIN_GAME_WINDOW_H_
#define JOIN_GAME_WINDOW_H_

#include <vector>
#include "../Button.h"
#include "../GameWindow.h"
#include "GameStateMsg.h"
#include "Text.h"
#include "Texture.h"

namespace GUI {
class JoinGameWindow : public GameWindow {
   public:
    JoinGameWindow(Window &window, Font &font, Camera &cam, std::vector<IO::GameInfo> &info);
    std::vector<IO::GameInfo> &info;
    uint8_t currentGameIndex{0};

    void start() override;
    void render() override;
    void handleKeyDown(SDL_Keycode key) override;
    void appendCharacter(char text[32]) override;
    void buttonPressed(ScreenPosition sp) override;

   private:
    Text gameName;
    Text numPlayers;
    Button prev;
    Button next;
    Button join;
};
}  // namespace GUI

#endif
