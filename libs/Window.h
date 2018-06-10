/*
 * Created by Federico Manuel Gomez Peter
 * Date: 17/05/18.
 */

#ifndef __Window_H__
#define __Window_H__

#include <SDL2/SDL.h>

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800

namespace GUI {
class Window {
   public:
    Window();
    Window(int width, int height);
    ~Window();

    void maximize();
    void clear();
    void clear(SDL_Color color);
    void render();
    SDL_Renderer &getRenderer();

    int getWidth();
    int getHeight();

   private:
    SDL_Window *window{nullptr};
    SDL_Renderer *renderer{nullptr};
    void close();
};
}  // namespace GUI

#endif  //__Window_H__
