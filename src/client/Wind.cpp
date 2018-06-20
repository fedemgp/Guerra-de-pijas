/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 20/06/18
 */

#include <WrapTexture.h>
#include "Wind.h"
#include "Texture.h"

GUI::Wind::Wind(const GUI::GameTextureManager &tex,
                GUI::Camera &cam):
        tex(tex), cam(cam){}

void GUI::Wind::render(std::int8_t intensity, int windowWidth){
    const GUI::Texture &toUse = (intensity > 0)?
                                this->tex.get(GameTextures::WindRight) :
                                this->tex.get(GameTextures::WindLeft);
    float scaledIntensity = (float) std::abs(intensity) / 127 * this->cam.getScale();
    GUI::WrapTexture wt{toUse, scaledIntensity, (float) toUse.getHeight() /
            this->cam.getScale()};
    GUI::ScreenPosition p{windowWidth, toUse.getHeight()};
    wt.renderFixed(p, this->cam);
}
