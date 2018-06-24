//
// Created by rodrigo on 19/06/18.
//

#ifndef INC_4_WORMS_GAMEWINDOW_H
#define INC_4_WORMS_GAMEWINDOW_H


#include <Camera.h>
#include "Font.h"
#include <Window.h>
#include <vector>
#include "Subject.h"
#include "Button.h"

namespace GUI {
    struct TextField {
        TextField(std::string &text, ScreenPosition sp, int height, int width, Font &font) :
                inputText(sp, height, width, text, font),
                focus(false) {};

        void selected(ScreenPosition sp) {
            this->focus = inputText.inside(sp);
        };
        
        void render(GUI::Camera &cam) {
            this->inputText.render(cam);
        };

        void appendCharacter(char *text) {
            this->inputText.msg += text;
        }
        
        Button inputText;
        bool focus;
    };

    class GameWindow : public Subject {
    public:
        unsigned int buttonSelected{0};

        explicit GameWindow(Window &window, Font &font, Camera &cam);

        virtual void start() = 0;
        virtual void render() = 0;
        virtual void appendCharacter(char text[32]) = 0;
        virtual void buttonPressed(ScreenPosition sp) = 0;

    protected:
        Window &window;
        Font &font;
        Camera &cam;
        std::vector<TextField> textFields;
        bool quit{false};
    };
}


#endif //INC_4_WORMS_GAMEWINDOW_H
