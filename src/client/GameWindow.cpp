//
// Created by rodrigo on 19/06/18.
//

#include <Font.h>
#include <Camera.h>
#include "GameWindow.h"

GUI::GameWindow::GameWindow(Window &window, Font &font, Camera &cam) :
        window(window),
        font(font),
        cam(cam) {
}
