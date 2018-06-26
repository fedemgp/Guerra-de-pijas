//
// Created by rodrigo on 26/06/18.
//

#ifndef INC_4_WORMS_GAMEENDWINDOW_H
#define INC_4_WORMS_GAMEENDWINDOW_H


#include <vector>

#include "Window.h"
#include "Font.h"
#include "GameStateMsg.h"
#include "GameWindow.h"
#include "Button.h"


namespace GUI {
    class GameEndWindow : public GameWindow {
    public:
        explicit GameEndWindow(GUI::Window &window, GUI::Font &font, GUI::Camera &cam, bool youWin);

        void start() override;
        void render() override;
        void handleKeyDown(SDL_Keycode key) override;
        void appendCharacter(char text[32]) override;
        void buttonPressed(ScreenPosition sp) override;

    private:
        std::vector<Button> buttons;
        int textSize{50};
        std::string gameEndResultMsg;
    };
}


#endif //INC_4_WORMS_GAMEENDWINDOW_H
