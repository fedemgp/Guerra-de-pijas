#ifndef TEXT_H_
#define TEXT_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "Camera.h"

namespace GUI {
class Text {
   public:
    Text(TTF_Font *font);
    ~Text();

    void set(const std::string &text, SDL_Color color);

    void render(Position p, Camera &camera);
    void renderFixed(ScreenPosition p, Camera &camera);

   private:
    void createTexture(SDL_Renderer *renderer);

    /* internal texture to represent the text in screen. */
    Texture *texture{nullptr};
    /* text content to render. */
    std::string text;
    /* whether the texture should be rendered. */
    bool needs_render{true};
    /* the font to use. */
    TTF_Font *font{nullptr};
    SDL_Color color;
};
}  // namespace GUI

#endif
