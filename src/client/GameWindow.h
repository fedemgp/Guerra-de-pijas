//
// Created by rodrigo on 19/06/18.
//

#ifndef INC_4_WORMS_GAMEWINDOW_H
#define INC_4_WORMS_GAMEWINDOW_H


#include <vector>

#include "Button.h"
#include "Camera.h"
#include "Font.h"
#include "Subject.h"
#include "Window.h"

#define ASSETS_PATH "assets"


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
            if (this->emptyString) {
                this->inputText.msg = text;
                this->emptyString = false;
            } else {
                this->inputText.msg += text;
            }
        };

        void backSpace() {
            if (!this->emptyString) {
                this->inputText.msg.pop_back();
                if (this->inputText.msg.length() == 0) {
                    this->inputText.msg = " ";
                    this->emptyString = true;
                }
            }
        };

        Button inputText;
        bool focus;

    private:
        bool emptyString{true};
    };

    class GameWindow : public Subject {
    public:
        uint8_t buttonSelected{0};

        explicit GameWindow(Window &window, Font &font, Camera &cam);

        virtual void start() = 0;
        virtual void render() = 0;
        virtual void handleKeyDown(SDL_Keycode key) = 0;
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
