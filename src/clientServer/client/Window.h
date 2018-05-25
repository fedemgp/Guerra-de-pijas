/*
 * Created by Federico Manuel Gomez Peter
 * Date: 17/05/18.
 */

#ifndef __Window_H__
#define __Window_H__

#include <SDL2/SDL.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

namespace GUI {
class Window {
   public:
    const int width, height;

    Window();
    Window(int width, int height);
    ~Window();
    void clear();
    void render();
    SDL_Renderer &getRenderer();

   private:
    SDL_Window *window{nullptr};
    SDL_Renderer *renderer{nullptr};
    void close();
};
}  // namespace GUI

#endif  //__Window_H__
