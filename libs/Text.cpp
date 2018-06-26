#include "Text.h"
#include <random>
#include "Exception.h"

std::unordered_map<GUI::TextCacheKey, GUI::TexturePtr, GUI::TextKeyHash> GUI::Text::cache;

GUI::Text::Text(GUI::Font& font) : font(font) {}

GUI::Text::~Text() {}

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

    float scale = float(this->size) / float(this->font.size);

    if (this->hasBackground) {
        GUI::ScreenPosition sp = camera.globalToScreen(p);

        SDL_Renderer& renderer = camera.getRenderer();
        SDL_SetRenderDrawColor(&renderer, this->background.r, this->background.g,
                               this->background.b, 255);

        SDL_Rect r = {};
        r.x = sp.x - this->texture->getWidth() * scale / 2;
        r.y = sp.y - (this->texture->getHeight() * scale - 10) / 2;
        r.w = this->texture->getWidth() * scale;
        r.h = this->texture->getHeight() * scale - 10;

        SDL_RenderFillRect(&renderer, &r);
    }

    SDL_Rect clip = {0, 0, this->texture->getWidth(), this->texture->getHeight()};
    camera.draw(*this->texture, p, clip, SDL_FLIP_NONE, scale);
}

/**
 * @brief Renders the text in a screen coordintates.
 *
 * @param p Position where the text will be rendered in screen coordintaes.
 * @param camera Camera.
 */
void GUI::Text::renderFixed(GUI::ScreenPosition p, GUI::Camera& camera) {
    this->render(camera.screenToGlobal(p), camera);
}

/**
 * @brief Creates a texture for the current text.
 *
 * @param renderer Renderer.
 */
void GUI::Text::createTexture(SDL_Renderer* renderer) {
    /* checks if the texture is already in the cache */
    uint32_t color = 0 | this->color.r << 16 | this->color.g << 8 | this->color.b;
    TextCacheKey key{this->text, color};
    if (GUI::Text::cache.find(key) != GUI::Text::cache.end()) {
        this->texture = GUI::Text::cache.at(key);
        return;
    }

    /* if the cache is full, removes a random entry */
    if (Text::cache.size() >= 150) {
        std::mt19937 rng;
        rng.seed(std::random_device()());
        std::uniform_int_distribution<std::mt19937::result_type> r(0, Text::cache.size() - 1);
        auto random_it = std::next(std::begin(Text::cache), r(rng));
        Text::cache.erase(random_it);
    }

    /* render text surface */
    SDL_Surface* surface = TTF_RenderText_Solid(this->font.get(), text.c_str(), this->color);
    if (surface == NULL) {
        throw Exception{"Failed rendering text surface: %s", TTF_GetError()};
    }

    /* convert to a texture */
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL) {
        SDL_FreeSurface(surface);
        throw Exception{"Failed create texture from rendered text: %s", SDL_GetError()};
    }

    GUI::Text::cache[key] = TexturePtr(new Texture{texture, surface->w, surface->h});
    this->texture = GUI::Text::cache[key];

    SDL_FreeSurface(surface);
}
