#ifndef TEXT_H_
#define TEXT_H_

#include <SDL2/SDL.h>
#include <string>
#include "Camera.h"
#include "Font.h"

namespace GUI {
class Text {
   public:
    Text(Font &font);
    ~Text();

    void set(const std::string &text, SDL_Color color);
    void set(const std::string &text, SDL_Color color, int size);
    void setBackground(SDL_Color color);

    void render(Position p, Camera &camera);
    void renderFixed(ScreenPosition p, Camera &camera);

   private:
    void createTexture(SDL_Renderer *renderer);

    bool hasBackground{false};
    SDL_Color background;
    /* internal texture to represent the text in screen. */
    Texture *texture{nullptr};
    /* text content to render. */
    std::string text;
    /* whether the texture should be rendered. */
    bool needs_render{true};
    /* the font to use. */
    Font &font;
    SDL_Color color;
    int size;
};
}  // namespace GUI

#endif
