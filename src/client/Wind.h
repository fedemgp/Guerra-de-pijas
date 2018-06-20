/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 20/06/18
 */

#ifndef __WIND_H__
#define __WIND_H__

#include <Camera.h>
#include "GameTextures.h"

namespace GUI{
    /**
     *  @brief receives the snapshot's intensity and draws the help interface
     *  to show the wind's intensity.
     */
    class Wind{
    public:
        Wind(const GameTextureManager &textureManager, Camera &cam);
        ~Wind() = default;
        void render(std::int8_t intensity, int windowWidth);

    private:
        const GameTextureManager &tex;
        Camera &cam;
    };
}

#endif //__WIND_H__
