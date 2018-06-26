//
// Created by rodrigo on 20/06/18.
//

#ifndef INC_4_WORMS_BUTTON_H
#define INC_4_WORMS_BUTTON_H


#include <Camera.h>
#include <Text.h>

namespace GUI {
    class Button {
    public:
        GUI::ScreenPosition position{0, 0};
        int height{0};
        int width{0};
        std::string msg;
        SDL_Color textColor{0, 0, 0};
        int textSize{10};

        Button(ScreenPosition sp, int height, int width, const std::string &msg, Font &font);
        Button(const std::string &msg, GUI::Font &font, SDL_Color textColor, int textSize);
        Button(const std::string &msg, Font &font);
        Button(ScreenPosition sp, int height, int width, Font &font);

        bool inside(ScreenPosition sp);
        void render(GUI::Camera &cam);

        void setBackground(SDL_Color color);

    private:
        Text text;
    };
}

#endif //INC_4_WORMS_BUTTON_H
