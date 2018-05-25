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
 * @brief Renders a texture's portion.
 *
 * @param renderer The renderer instance.
 * @param clip Portion of the texture to render.
 * @param dst Position where the texture will be rendered.
 * @param flip Texture flip type.
 */
void GUI::Texture::render(SDL_Renderer &renderer, SDL_Rect clip, SDL_Rect dst,
                          SDL_RendererFlip flip) const {
    /* set rendering space and render to screen */
    dst.x -= clip.w / 2;
    dst.y -= clip.h / 2;
    SDL_RenderCopyEx(&renderer, this->texture, &clip, &dst, 0, nullptr, flip);
}

/**
 * @brief Renders the complete texture.
 *
 * @param renderer Renderer.
 * @param dst Position where texture will be rendered.
 */
void GUI::Texture::render(SDL_Renderer &renderer, SDL_Rect dst) const {
    dst.w = this->width;
    dst.h = this->height;
    dst.x -= this->width / 2;
    dst.y -= this->height / 2;
    SDL_RenderCopy(&renderer, this->texture, NULL, &dst);
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
