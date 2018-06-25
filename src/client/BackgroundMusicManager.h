//
// Created by rodrigo on 25/06/18.
//

#ifndef INC_4_WORMS_BACKGROUNDMUSICMANAGER_H
#define INC_4_WORMS_BACKGROUNDMUSICMANAGER_H

#include <SDL2/SDL.h>
#include <functional>
#include <string>
#include <unordered_map>
#include "BackgroundMusic.h"

namespace GUI {
    template <typename ID, typename HASH = std::hash<ID>>
    class BackgroundMusicManager {
    public:
        BackgroundMusicManager();
        ~BackgroundMusicManager();
        BackgroundMusicManager& operator=(BackgroundMusicManager& other) = delete;

        void load(ID id, const std::string& file_name);
        const BackgroundMusic& get(ID id) const;

    private:
        std::unordered_map<ID, BackgroundMusic, HASH> cache;
    };
}  // namespace GUI

template <typename ID, typename HASH>
GUI::BackgroundMusicManager<ID, HASH>::BackgroundMusicManager() {}

template <typename ID, typename HASH>
GUI::BackgroundMusicManager<ID, HASH>::~BackgroundMusicManager() {}

/**

 * @brief Loads a background music file.
 *
 * @param file_name The image file name.
 */
template <typename ID, typename HASH>
void GUI::BackgroundMusicManager<ID, HASH>::load(ID id, const std::string& file_name) {
    GUI::BackgroundMusic backgroundMusic{file_name};
    this->cache.insert(std::make_pair(id, std::move(backgroundMusic)));
}

/**
 * @brief Gets a background music.
 *
 * @param file_name Name of the background music.
 */
template <typename ID, typename HASH>
const GUI::BackgroundMusic& GUI::BackgroundMusicManager<ID, HASH>::get(ID id) const {
    return this->cache.at(id);
}

#endif //INC_4_WORMS_BACKGROUNDMUSICMANAGER_H
