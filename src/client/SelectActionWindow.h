//
// Created by rodrigo on 19/06/18.
//

#ifndef INC_4_WORMS_SELECTACTIONWINDOW_H
#define INC_4_WORMS_SELECTACTIONWINDOW_H


#include <vector>

#include "Window.h"
#include "Font.h"
#include "GameWindow.h"
#include "Button.h"

namespace GUI {
    class SelectActionWindow : public GameWindow {
    public:
        explicit SelectActionWindow(Window &window, Font &font, Camera &cam);

        void start() override;
        void render() override;
        void buttonPressed(ScreenPosition sp) override;

    private:
        std::vector<Button> buttons;
    };
}


#endif //INC_4_WORMS_SELECTACTIONWINDOW_H
