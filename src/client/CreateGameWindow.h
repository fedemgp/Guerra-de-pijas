//
// Created by rodrigo on 23/06/18.
//

#ifndef INC_4_WORMS_CREATEGAMEWINDOW_H
#define INC_4_WORMS_CREATEGAMEWINDOW_H


#include <vector>

#include "Window.h"
#include "Font.h"
#include "GameStateMsg.h"
#include "GameWindow.h"
#include "Button.h"

#define SELECT_LEVEL_MSG "Select"
#define LEVEL_MSG "Level"
#define PLAYERS_MSG "Players"
#define NEXT_LEVEL_MSG "Next"
#define PREVIOUS_LEVEL_MSG "Previous"

namespace GUI {
    class CreateGameWindow : public GameWindow {
    public:
        std::vector<IO::LevelInfo> &levelsInfo;
        
        explicit CreateGameWindow(GUI::Window &window, GUI::Font &font, GUI::Camera &cam,
                                  std::vector<IO::LevelInfo> &levelsInfo);

        void start() override;
        void render() override;
        void appendCharacter(char text[32]) override;
        void buttonPressed(ScreenPosition sp) override;

    private:
        std::vector<Button> buttons;
        int levelInfoSize{30};
    };
}


#endif //INC_4_WORMS_CREATEGAMEWINDOW_H
