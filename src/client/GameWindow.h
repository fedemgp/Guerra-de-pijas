//
// Created by rodrigo on 19/06/18.
//

#ifndef INC_4_WORMS_GAMEWINDOW_H
#define INC_4_WORMS_GAMEWINDOW_H


#include <Window.h>
#include "../server/Subject.h"

namespace GUI {
    class GameWindow : public Subject {
    public:
        explicit GameWindow(Window &window);

        virtual void start() = 0;
        virtual void render() = 0;

    protected:
        Window &window;
        bool quit{false};
    };
}


#endif //INC_4_WORMS_GAMEWINDOW_H
