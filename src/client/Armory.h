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
#include <GameStateMsg.h>
#include <Text.h>
#include "GameTextures.h"

namespace GUI {
class Armory {
   public:
    Armory(const GameTextureManager &textureManager, Camera &cam, Font &font);
    ~Armory() = default;
    void loadWeapons();
    void render();
    void update(IO::GameStateMsg &msg);

   private:
    const GameTextureManager &manager;
    Camera &camera;
    std::vector<const Texture *> weaponIcons;
    const Font &font;
    Text weaponButton;
    std::vector<std::int16_t> ammunition;
};
}  // namespace GUI

#endif  //__ARMORY_H__
