//
// Created by rodrigo on 4/06/18.
//

#ifndef INC_4_WORMS_SOUNDEFFECTMANAGER_H
#define INC_4_WORMS_SOUNDEFFECTMANAGER_H

#include <SDL2/SDL.h>
#include <functional>
#include <string>
#include <unordered_map>
#include "SoundEffect.h"

namespace GUI {
template <typename ID, typename HASH = std::hash<ID>>
class SoundEffectManager {
   public:
    SoundEffectManager();
    ~SoundEffectManager();
    SoundEffectManager& operator=(SoundEffectManager& other) = delete;

    void load(ID id, const std::string& file_name);
    const SoundEffect& get(ID id) const;

   private:
    std::unordered_map<ID, SoundEffect, HASH> cache;
};
}  // namespace GUI

template <typename ID, typename HASH>
GUI::SoundEffectManager<ID, HASH>::SoundEffectManager() {}

template <typename ID, typename HASH>
GUI::SoundEffectManager<ID, HASH>::~SoundEffectManager() {}

/**

 * @brief Loads a sound effect.
 *
 * @param file_name The image file name.
 */
template <typename ID, typename HASH>
void GUI::SoundEffectManager<ID, HASH>::load(ID id, const std::string& file_name) {
    GUI::SoundEffect soundEffect{file_name};
    this->cache.insert(std::make_pair(id, std::move(soundEffect)));
}

/**
 * @brief Gets a sound effect.
 *
 * @param file_name Name of the sound effect.
 */
template <typename ID, typename HASH>
const GUI::SoundEffect& GUI::SoundEffectManager<ID, HASH>::get(ID id) const {
    return this->cache.at(id);
}

#endif  // INC_4_WORMS_SOUNDEFFECTMANAGER_H
