//
// Created by rodrigo on 20/06/18.
//

#include <Font.h>
#include "Button.h"

GUI::Button::Button(ScreenPosition sp, int height, int width, const std::string &msg, Font &font) :
        position(sp),
        height(height),
        width(width),
        msg(msg),
        textColor(SDL_Color{0xFF, 0xFF, 0xFF}),
        textSize(40),
        text(font) {
    this->text.set(this->msg, SDL_Color{0xFF, 0xFF, 0xFF}, 40);
}

GUI::Button::Button(const std::string &msg, GUI::Font &font, SDL_Color textColor, int textSize) :
        msg(msg),
        textColor(textColor),
        textSize(textSize),
        text(font) {
    this->text.set(this->msg, textColor, textSize);
}

GUI::Button::Button(const std::string &msg, GUI::Font &font) :
        msg(msg),
        text(font) {
}

GUI::Button::Button(GUI::ScreenPosition sp, int height, int width, GUI::Font &font) :
        position(sp),
        height(height),
        width(width),
        text(font) {

}

void GUI::Button::render(GUI::Camera &cam) {
    SDL_Rect fillRect = {this->position.x - this->width / 2, this->position.y + this->height / 2,
                         this->width / (int) cam.getScale(), this->height / (int) cam.getScale()};
    cam.drawLocal(ScreenPosition{this->position.x, this->position.y}, fillRect, SDL_Color{0, 0, 0});
    this->text.set(this->msg, this->textColor, this->textSize);
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

void GUI::Button::setBackground(SDL_Color color) {
    this->text.setBackground(color);
}
