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

    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            Position pos{p.x + this->texture.getWidth() * i, p.y + this->texture.getHeight() * j};
            camera.draw(this->texture, pos);
        }
    }

    int x_remainder = this->width % this->texture.getWidth();
    int y_remainder = this->height % this->texture.getHeight();

    if (x_remainder > 0) {
        for (int i = 0; i < rows; i++) {
            Position pos{p.x + this->texture.getWidth() * cols,
                         p.y + this->texture.getHeight() * i};
            SDL_Rect clip = {0, 0, x_remainder, this->height};

            camera.draw(this->texture, pos, clip);
        }
    }

    if (y_remainder > 0) {
        for (int i = 0; i < cols; i++) {
            Position pos{p.x + this->texture.getWidth() * i,
                         p.y + this->texture.getHeight() * rows};
            SDL_Rect clip = {0, 0, this->width, y_remainder};

            camera.draw(this->texture, pos, clip);
        }
    }

    if (x_remainder > 0 && y_remainder > 0) {
        SDL_Rect clip = {0, 0, x_remainder, y_remainder};
        Position pos{p.x + this->texture.getWidth() * cols, p.y + this->texture.getHeight() * rows};
        camera.draw(this->texture, pos, clip);
    }
}
