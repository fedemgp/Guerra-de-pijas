/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 10/06/18
 */

#ifndef __ARMORY_H__
#define __ARMORY_H__

#define BUTTON_ROOT_STR "F"

#include <vector>

#include <Animation.h>
#include <Font.h>
#include "GameTextures.h"
#include <Text.h>

namespace GUI{
    class Armory{
    public:
        Armory(const GameTextureManager &textureManager, Camera &cam, Font &font);
        ~Armory() = default;
        void loadWeapons();
        void render();

    private:
        const GameTextureManager &manager;
        Camera &camera;
        std::vector<const Texture *> weaponIcons;
        const Font &font;
        Text weaponButton;
    };
} // namespace GUI


#endif //__ARMORY_H__
