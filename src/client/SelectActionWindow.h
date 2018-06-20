//
// Created by rodrigo on 19/06/18.
//

#ifndef INC_4_WORMS_SELECTACTIONWINDOW_H
#define INC_4_WORMS_SELECTACTIONWINDOW_H


#include <Window.h>
#include "GameWindow.h"

namespace GUI {
    class SelectActionWindow : public GameWindow {
    public:
        explicit SelectActionWindow(Window &window);

        void start() override;
        void render() override;
    };
}


#endif //INC_4_WORMS_SELECTACTIONWINDOW_H
