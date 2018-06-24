//
// Created by rodrigo on 23/06/18.
//

#ifndef INC_4_WORMS_CREATEGAMEWINDOW_H
#define INC_4_WORMS_CREATEGAMEWINDOW_H


#include <vector>

#include "Window.h"
#include "Font.h"
#include "GameWindow.h"
#include "Button.h"

#define SELECT_LEVEL_MSG "Select"

namespace GUI {
    class CreateGameWindow : public GameWindow {
    public:
        explicit CreateGameWindow(GUI::Window &window, GUI::Font &font, GUI::Camera &cam,
                                  std::vector<IO::LevelInfo> &levelsInfo);

        void start() override;
        void render() override;
        void buttonPressed(ScreenPosition sp) override;

    private:
        std::vector<Button> buttons;
        std::vector<IO::LevelInfo> &levelsInfo;
        int levelInfoSize{30};
    };
}


#endif //INC_4_WORMS_CREATEGAMEWINDOW_H
