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

    void start() override;
    void render() override;
    void buttonPressed(ScreenPosition sp) override;

   private:
    uint8_t currentGameIndex{0};
    Text gameName;
    Button prev;
    Button next;
    std::vector<IO::GameInfo> &info;
};
}  // namespace GUI

#endif
