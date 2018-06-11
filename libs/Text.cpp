#include "Text.h"
#include "Exception.h"

GUI::Text::Text(GUI::Font& font) : font(font) {}

GUI::Text::~Text() {
    if (this->texture) {
        delete this->texture;
    }
}

void GUI::Text::setBackground(SDL_Color color) {
    this->hasBackground = true;
    this->background = color;
    this->needs_render = true;
}

void GUI::Text::set(const std::string& text, SDL_Color color) {
    this->set(text, color, this->font.size);
}

void GUI::Text::set(const std::string& text, SDL_Color color, int size) {
    this->size = size;
    this->text = text;
    this->color = color;
    this->needs_render = true;
}

void GUI::Text::render(GUI::Position p, GUI::Camera& camera) {
    if (this->needs_render) {
        this->createTexture(&camera.getRenderer());
        this->needs_render = false;
    }

    if (this->hasBackground) {
        GUI::ScreenPosition sp = camera.globalToScreen(p);

        SDL_Renderer& renderer = camera.getRenderer();
        SDL_SetRenderDrawColor(&renderer, this->background.r, this->background.g,
                               this->background.b, 255);

        SDL_Rect r = {};
        r.x = sp.x - this->texture->getWidth() / 2;
        r.y = sp.y - (this->texture->getHeight() - 10) / 2;
        r.w = this->texture->getWidth();
        r.h = this->texture->getHeight() - 10;

        SDL_RenderFillRect(&renderer, &r);
    }

    SDL_Rect clip = {0, 0, this->texture->getWidth(), this->texture->getHeight()};
    float scale = float(this->size) / float(this->font.size);
    camera.draw(*this->texture, p, clip, SDL_FLIP_NONE, scale);
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
    SDL_Rect clip = {0, 0, this->texture->getWidth(), this->texture->getHeight()};
    float scale = float(this->size) / float(this->font.size);
    camera.drawLocal(*this->texture, p, clip, SDL_FLIP_NONE, scale);
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
    SDL_Surface* surface = TTF_RenderText_Solid(this->font.get(), text.c_str(), color);
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
