#include "Font.h"
#include "Exception.h"

GUI::Font::Font(const std::string &file, int size) : size(size) {
    this->font = TTF_OpenFont(file.c_str(), size);
    if (!this->font) {
        throw Exception{"Failed loading the font: %s", TTF_GetError()};
    }
}

GUI::Font::~Font() {
    TTF_CloseFont(this->font);
}

/**
 * @brief Gets the SDL font pointer.
 */
TTF_Font *GUI::Font::get() {
    return this->font;
}
