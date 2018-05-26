#include "Texture.h"
#include <SDL2/SDL_image.h>
#include <cassert>
#include "Exception.h"

GUI::Texture::Texture(const std::string &filename, SDL_Renderer &renderer, GUI::Color key) {
    /* loads the image into a temporary surface */
    SDL_Surface *tmp = IMG_Load(filename.c_str());
    if (!tmp) {
        throw Exception{"Error loading %s: %s", filename.c_str(), IMG_GetError()};
    }

    SDL_SetColorKey(tmp, SDL_TRUE, SDL_MapRGB(tmp->format, key.r, key.g, key.b));

    /* creates a texture from the surface */
    this->texture = SDL_CreateTextureFromSurface(&renderer, tmp);
    if (!this->texture) {
        SDL_FreeSurface(tmp);
        throw Exception{"Error creating texture for %s: %s", filename.c_str(), SDL_GetError()};
    }

    this->height = tmp->h;
    this->width = tmp->w;

    /* releases the temporary surface */
    SDL_FreeSurface(tmp);
}

GUI::Texture::Texture(SDL_Texture *texture, int width, int height)
    : height(height), width(width), texture(texture) {
    if (!texture) {
        throw Exception{"Texture cannot be NULL"};
    }
}

/**
 * @brief Move constructor.
 *
 * @param other Instance to move.
 */
GUI::Texture::Texture(Texture &&other) {
    this->height = other.height;
    this->width = other.width;
    std::swap(this->texture, other.texture);
}

GUI::Texture::~Texture() {
    if (this->texture) {
        SDL_DestroyTexture(this->texture);
    }
}

/**
 * @brief Gets the texture's width.
 *
 * @return int width.
 */
int GUI::Texture::getWidth() const {
    return this->width;
}

/**
 * @brief Gets the texture's height.
 *
 * @return int Height.
 */
int GUI::Texture::getHeight() const {
    return this->height;
}

/**
 * @brief Returns the internal SDL texture.
 *
 * @return SDL texture.
 */
SDL_Texture *GUI::Texture::get() const {
    return this->texture;
}
