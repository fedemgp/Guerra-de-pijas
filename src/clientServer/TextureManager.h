#ifndef TEXTURE_MANAGER_H_
#define TEXTURE_MANAGER_H_

#include <SDL2/SDL.h>
#include <functional>
#include <string>
#include <unordered_map>
#include "Texture.h"

namespace GUI {
template <typename ID, typename HASH = std::hash<ID>>
class TextureManager {
   public:
    TextureManager(SDL_Renderer& renderer);
    ~TextureManager();
    TextureManager& operator=(TextureManager& other) = delete;

    void load(ID id, const std::string& file_name, Color key);
    const Texture& get(ID id) const;

   private:
    std::unordered_map<ID, Texture, HASH> cache;
    SDL_Renderer& renderer;
};
}  // namespace GUI

template <typename ID, typename HASH>
GUI::TextureManager<ID, HASH>::TextureManager(SDL_Renderer& renderer) : renderer(renderer) {}

template <typename ID, typename HASH>
GUI::TextureManager<ID, HASH>::~TextureManager() {}

/**

 * @brief Loads a texture.
 *
 * @param file_name The image file name.
 * @param renderer Renderer.
 */
template <typename ID, typename HASH>
void GUI::TextureManager<ID, HASH>::load(ID id, const std::string& file_name, GUI::Color key) {
    GUI::Texture texture{file_name, this->renderer, key};
    this->cache.insert(std::make_pair(id, std::move(texture)));
}

/**
 * @brief Gets a texture.
 *
 * @param file_name Name of the texture.
 */
template <typename ID, typename HASH>
const GUI::Texture& GUI::TextureManager<ID, HASH>::get(ID id) const {
    return this->cache.at(id);
}

#endif
