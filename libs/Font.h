#ifndef FONT_H_
#define FONT_H_

#include <SDL2/SDL_ttf.h>
#include <string>

namespace GUI {
class Font {
   public:
    const int size;

    Font(const std::string &file, int size);
    ~Font();

    TTF_Font *get();

   private:
    TTF_Font *font;
};

}  // namespace GUI

#endif
