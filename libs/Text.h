#ifndef TEXT_H_
#define TEXT_H_

#include <SDL2/SDL.h>
#include <cstdint>
#include <functional>
#include <list>
#include <memory>
#include <string>
#include <unordered_map>
#include "Camera.h"
#include "Font.h"

namespace GUI {
using TextCacheKey = std::pair<std::string, uint32_t>;

struct TextKeyHash {
    size_t operator()(const TextCacheKey &p) const {
        return std::hash<std::string>{}(p.first) ^ p.second;
    }
};

using TexturePtr = std::shared_ptr<Texture>;

class Text {
   public:
    Text(Font &font);
    ~Text();

    void set(const std::string &text, SDL_Color color);
    void set(const std::string &text, SDL_Color color, int size);
    void setBackground(SDL_Color color);

    void render(Position p, Camera &camera);
    void renderFixed(ScreenPosition p, Camera &camera);

   protected:
    static std::unordered_map<TextCacheKey, TexturePtr, TextKeyHash> cache;

   private:
    void createTexture(SDL_Renderer *renderer);

    bool hasBackground{false};
    SDL_Color background;
    /* internal texture to represent the text in screen. */
    TexturePtr texture;
    /* text content to render. */
    std::string text;
    /* whether the texture should be rendered. */
    bool needs_render{true};
    /* the font to use. */
    Font &font;
    SDL_Color color;
    int size{-1};
};
}  // namespace GUI

#endif
