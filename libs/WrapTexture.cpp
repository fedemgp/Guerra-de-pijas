#include "WrapTexture.h"

GUI::WrapTexture::WrapTexture(const GUI::Texture& texture, float width, float height)
    : texture(texture), width(width), height(height) {}

GUI::WrapTexture::~WrapTexture() {}

/**
 * @brief Renders the texture wrapped.
 *
 * @param p Position where to render.
 * @param camera Camera.
 */
void GUI::WrapTexture::render(GUI::Position p, Camera& camera) {
    this->render(p, 0.0f, camera);
}

/**
 * @brief Renders the texture wrapped with the given angle.
 *
 * @param p Position where to render.
 * @param angle Render angle.
 * @param camera Camera.
 */
void GUI::WrapTexture::render(GUI::Position p, float angle, Camera& camera) {
    int width = this->width * camera.getScale();
    int height = this->height * camera.getScale();

    int cols = width / this->texture.getWidth();
    int rows = height / this->texture.getHeight();

    int x_remainder = width % this->texture.getWidth();
    int y_remainder = height % this->texture.getHeight();


    ScreenPosition sp = camera.globalToScreen(p);
    sp.x -= width / 2;
    sp.y -= height / 2;

    SDL_Renderer* renderer = &camera.getRenderer();
    int tw = this->texture.getWidth();
    int th = this->texture.getHeight();

    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            ScreenPosition pos{sp.x + tw * i, sp.y - th * j};
            ScreenPosition rcenter = sp - pos;
            SDL_Point center = {rcenter.x + width / 2, rcenter.y + height / 2};

            SDL_Rect dst = {pos.x, pos.y, tw, th};
            SDL_RenderCopyEx(renderer, this->texture.get(), NULL, &dst, -angle, &center,
                             SDL_FLIP_NONE);
        }

        if (y_remainder) {
            ScreenPosition pos{sp.x + tw * i, sp.y - th * rows};
            ScreenPosition rcenter = sp - pos;
            SDL_Point center = {rcenter.x + width / 2, rcenter.y + height / 2};

            SDL_Rect clip = {0, 0, tw, y_remainder};
            SDL_Rect dst = {pos.x, pos.y, tw, y_remainder};
            SDL_RenderCopyEx(renderer, this->texture.get(), &clip, &dst, -angle, &center,
                             SDL_FLIP_NONE);
        }
    }

    if (x_remainder > 0) {
        for (int i = 0; i < rows; i++) {
            ScreenPosition pos{sp.x + tw * cols, sp.y - th * i};
            ScreenPosition rcenter = sp - pos;
            SDL_Point center = {rcenter.x + width / 2, rcenter.y + height / 2};

            SDL_Rect clip = {0, 0, x_remainder, th};
            SDL_Rect dst = {pos.x, pos.y, x_remainder, th};
            SDL_RenderCopyEx(renderer, this->texture.get(), &clip, &dst, -angle, &center,
                             SDL_FLIP_NONE);
        }

        if (y_remainder) {
            ScreenPosition pos{sp.x + tw * cols, sp.y - th * rows};
            ScreenPosition rcenter = sp - pos;
            SDL_Point center = {rcenter.x + width / 2, rcenter.y + height / 2};

            SDL_Rect clip = {0, 0, x_remainder, y_remainder};
            SDL_Rect dst = {pos.x, pos.y, x_remainder, y_remainder};
            SDL_RenderCopyEx(renderer, this->texture.get(), &clip, &dst, -angle, &center,
                             SDL_FLIP_NONE);
        }
    }
}

void GUI::WrapTexture::renderFixed(GUI::ScreenPosition sp, Camera& camera) {
    sp.x -= this->width * camera.getScale() / 2;
    sp.y -= this->height * camera.getScale() / 2;
    this->render(camera.screenToGlobal(sp), camera);
}
