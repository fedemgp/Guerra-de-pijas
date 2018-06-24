//
// Created by rodrigo on 20/06/18.
//

#include <Font.h>
#include "Button.h"

GUI::Button::Button(ScreenPosition sp, int height, int width, std::string &msg, Font &font) :
        position(sp),
        height(height),
        width(width),
        text(font) {
    this->text.set(std::move(msg), SDL_Color{0xFF, 0xFF, 0xFF}, 40);
}

GUI::Button::Button(std::string &msg, GUI::Font &font, SDL_Color textColor, int textSize) :
        text(font) {
    this->text.set(std::move(msg), textColor, textSize);
}

GUI::Button::Button(std::string &msg, GUI::Font &font) :
        msg(std::move(msg)),
        text(font) {
}

void GUI::Button::render(GUI::Camera &cam, Window &window) {
    SDL_Rect fillRect = {this->position.x - this->width / 2, this->position.y + this->height / 2,
                         this->width / (int) cam.getScale(), this->height / (int) cam.getScale()};
    cam.drawLocal(ScreenPosition{this->position.x, this->position.y}, fillRect, SDL_Color{0, 0, 0});
    this->text.renderFixed(this->position, cam);
}

bool GUI::Button::inside(GUI::ScreenPosition sp) {
    bool inside = true;

    if(sp.x < this->position.x - this->width / 2) {
        //Mouse is left of the button
        inside = false;
    } else if(sp.x > this->position.x + this->width / 2) {
        //Mouse is right of the button
        inside = false;
    } else if(sp.y < this->position.y - this->height / 2) {
        //Mouse below the button
        inside = false;
    } else if(sp.y > this->position.y + this->width / 2) {
        //Mouse above the button
        inside = false;
    }

    return inside;
}
