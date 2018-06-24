//
// Created by rodrigo on 19/06/18.
//

#ifndef INC_4_WORMS_GAMEWINDOW_H
#define INC_4_WORMS_GAMEWINDOW_H


#include <Camera.h>
#include "Font.h"
#include <Window.h>
#include "Subject.h"

namespace GUI {
    class GameWindow : public Subject {
    public:
        int buttonSelected{0};

        explicit GameWindow(Window &window, Font &font, Camera &cam);

        virtual void start() = 0;
        virtual void render() = 0;
        virtual void buttonPressed(ScreenPosition sp) = 0;

    protected:
        Window &window;
        Font &font;
        Camera &cam;
        bool quit{false};
    };
}


#endif //INC_4_WORMS_GAMEWINDOW_H
