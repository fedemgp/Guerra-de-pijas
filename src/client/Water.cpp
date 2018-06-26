#include "Water.h"
#include <cmath>
#include "WrapTexture.h"

GUI::Water::Water(const GUI::GameTextureManager &tm) : textureManager(tm) {}

/**
 * @brief Updates the water animation state
 *
 * @param dt Time elapsed since the last call to this function.
 */
void GUI::Water::update(float dt) {
    this->elapsed += dt;
    this->yDelta = std::sin(this->elapsed) * 1;
}

/**
 * @brief Renders the water.
 *
 * @param camera Camera where the water is rendered.
 */
void GUI::Water::render(GUI::Camera &camera) {
    const GUI::Texture &texture = this->textureManager.get(GUI::GameTextures::Water);
    GUI::WrapTexture water{texture, camera.screenWidth(), texture.getHeight() / camera.getScale()};
    water.render(Position{camera.getPosition().x, -6.5f + this->yDelta}, camera);
}
