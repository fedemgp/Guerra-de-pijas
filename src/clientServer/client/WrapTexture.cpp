#include "WrapTexture.h"

GUI::WrapTexture::WrapTexture(const GUI::Texture& texture, int width, int height)
    : texture(texture), width(width), height(height) {}

GUI::WrapTexture::~WrapTexture() {}

/**
 * @brief Renders the texture wrapped.
 *
 * @param p Position where to render.
 * @param camera Camera.
 */
void GUI::WrapTexture::render(GUI::Position p, Camera& camera) {
    int cols = this->width / this->texture.getWidth();
    int rows = this->height / this->texture.getHeight();

    int x_remainder = this->width % this->texture.getWidth();
    int y_remainder = this->height % this->texture.getHeight();

    ScreenPosition sp = camera.globalToScreen(p);
    sp.x -= this->width / 2;
    int x_offset = this->texture.getWidth() / 2 + x_remainder / 2;

    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            ScreenPosition pos{sp.x + this->texture.getWidth() * i - x_offset,
                               sp.y + this->texture.getHeight() * j};
            camera.drawLocal(this->texture, pos);
        }

        if (y_remainder) {
            ScreenPosition pos{sp.x + this->texture.getWidth() * i + x_offset,
                               sp.y + this->texture.getHeight() * rows};
            SDL_Rect clip = {0, 0, this->width, y_remainder};

            camera.drawLocal(this->texture, pos, clip);
        }
    }

    x_offset = x_remainder / 2;
    if (x_remainder > 0) {
        for (int i = 0; i < rows; i++) {
            ScreenPosition pos{sp.x + this->texture.getWidth() * cols + x_offset,
                               sp.y + this->texture.getHeight() * i};
            SDL_Rect clip = {0, 0, x_remainder, this->height};

            camera.drawLocal(this->texture, pos, clip);
        }

        if (y_remainder) {
            ScreenPosition pos{sp.x + this->texture.getWidth() * cols + x_offset,
                               sp.y + this->texture.getHeight() * rows};
            SDL_Rect clip = {0, 0, x_remainder, y_remainder};

            camera.drawLocal(this->texture, pos, clip);
        }
    }
}
