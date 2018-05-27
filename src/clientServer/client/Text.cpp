#include "Text.h"
#include "Exception.h"

GUI::Text::Text(TTF_Font* font) : font(font) {}

GUI::Text::~Text() {
    if (this->texture) {
        delete this->texture;
    }
}

void GUI::Text::set(const std::string& text, SDL_Color color) {
    this->text = text;
    this->color = color;
    this->needs_render = true;
}

void GUI::Text::render(GUI::Position p, GUI::Camera& camera) {
    if (this->needs_render) {
        this->createTexture(&camera.getRenderer());
        this->needs_render = false;
    }

    camera.draw(*this->texture, p);
}

/**
 * @brief Renders the text in a screen coordintates.
 *
 * @param p Position where the text will be rendered in screen coordintaes.
 * @param camera Camera.
 */
void GUI::Text::renderFixed(GUI::ScreenPosition p, GUI::Camera& camera) {
    if (this->needs_render) {
        this->createTexture(&camera.getRenderer());
        this->needs_render = false;
    }

    camera.drawLocal(*this->texture, p);
}

/**
 * @brief Creates a texture for the current text.
 *
 * @param renderer Renderer.
 */
void GUI::Text::createTexture(SDL_Renderer* renderer) {
    if (this->texture) {
        delete this->texture;
    }

    /* render text surface */
    SDL_Surface* surface = TTF_RenderText_Solid(this->font, text.c_str(), color);
    if (surface == NULL) {
        throw Exception{"Failed rendering text surface: %s", TTF_GetError()};
    }

    /* convert to a texture */
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL) {
        SDL_FreeSurface(surface);
        throw Exception{"Failed create texture from rendered text: %s", SDL_GetError()};
    }

    this->texture = new Texture{texture, surface->w, surface->h};

    SDL_FreeSurface(surface);
}
