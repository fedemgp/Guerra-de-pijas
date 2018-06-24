//
// Created by rodrigo on 24/06/18.
//

#ifndef INC_4_WORMS_WAITINGPLAYERSWINDOW_H
#define INC_4_WORMS_WAITINGPLAYERSWINDOW_H


#include <vector>

#include "Window.h"
#include "Font.h"
#include "GameStateMsg.h"
#include "GameWindow.h"
#include "Button.h"

namespace GUI {
    class WaitingPlayersWindow : public GameWindow {
    public:
        uint8_t playersConnected{0};

        explicit WaitingPlayersWindow(GUI::Window &window, GUI::Font &font, GUI::Camera &cam, unsigned int playersQuantity);

        void start() override;
        void render() override;
        void buttonPressed(ScreenPosition sp) override;

    private:
        std::vector<Button> buttons;
        unsigned int playersQuantity{0};
    };
}


#endif //INC_4_WORMS_WAITINGPLAYERSWINDOW_H
