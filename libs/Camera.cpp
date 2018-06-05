#include "Camera.h"
#include <cmath>
#include <iostream>

/**
 * @brief Construct a new Camera with the given initial coordinates.
 *
 * @param p Initial coordinates.
 */
GUI::Camera::Camera(float scale, int width, int height, SDL_Renderer &renderer)
    : start(this->cur),
      dst(this->cur),
      scale(scale),
      width(width),
      height(height),
      renderer(renderer) {
    this->setTo(Position{0, float(this->height) / this->scale / 2.0f});
}

GUI::Camera::~Camera() {}

/**
 * @brief Whether the camera is currently moving to or not.
 */
bool GUI::Camera::isMoving() const {
    return (this->dst != this->cur);
}

/**
 * @brief Returns the internal renderer.
 *
 * @return Renderer.
 */
SDL_Renderer &GUI::Camera::getRenderer() const {
    return this->renderer;
}

/**
 * @brief Returns the pixel/meters scale.
 *
 * @return Scale.
 */
float GUI::Camera::getScale() const {
    return this->scale;
}

/**
 * @brief Returns the camera position in global coordinates.
 *
 * @return Position Camera position.
 */
GUI::Position GUI::Camera::getPosition() const {
    return this->cur;
}

/**
 * @brief Instantly moves the camera to the given coordinates.
 *
 * @param coord Coordinates of the new camera position.
 */
void GUI::Camera::setTo(GUI::Position coord) {
    this->elapsed = 0.0f;

    /* avoids the camera from going below the zero */
    coord.y = std::max(coord.y, (float(this->height) / this->scale) / 2);

    coord.x -= (this->width / 2) / this->scale;
    coord.y += (this->height / 2) / this->scale;
    this->dst = this->start = this->cur = coord;
}

/**
 * @brief Smoothly moves the camera to the given coordinates.
 *
 * @param coord Coordinates of the final camera position.
 */
void GUI::Camera::moveTo(GUI::Position coord) {
    /* avoids the camera from going below the zero */
    coord.y = std::max(coord.y, (float(this->height) / this->scale) / 2 - 10.0f);

    if (this->dst == coord) {
        return;
    }

    coord.x -= (this->width / 2) / this->scale;
    coord.y += (this->height / 2) / this->scale;

    this->elapsed = 0.0f;
    this->dst = coord;
    this->start = this->cur;
}

/**
 * @brief Converts some global coordinates to screen coordinates.
 *
 * @param global Global coordinates.
 * @return Corresponding screen coordinates.
 */
GUI::ScreenPosition GUI::Camera::globalToScreen(GUI::Position global) {
    /* converts from global to local/camera coordinates */
    Position local = (global - this->cur);
    local.y *= -1;

    /* calculates the screen coordinates */
    return ScreenPosition{int(local.x * this->scale), int(local.y * this->scale)};
}

/**
 * @brief Updates the camera according to the elapsed time since the last update.
 *
 * @param dt Seconds elapsed since the last update.
 */
void GUI::Camera::update(float dt) {
    if (this->dst == this->cur) {
        return;
    }

    /* total animation duration in seconds */
    const float duration = 5.0f;

    this->elapsed += dt;

    /* if the distance is less than the threshold, then it's set immediately */
    if (this->elapsed > duration || this->cur.distance(this->dst) < 0.05) {
        this->cur = this->dst;
        return;
    }

    /* calculates the new position */
    const float framerate = duration / 60.0f;
    float scale = 1.0f - 1.0f / std::pow(2, this->elapsed / framerate);
    this->cur = this->start + (this->dst - this->start) * scale;
}

void GUI::Camera::draw(const Texture &texture, Position p) {
    SDL_Rect clip = {0, 0, texture.getWidth(), texture.getHeight()};
    this->draw(texture, p, clip);
}

/**
 * @brief Draws a texture in the screen.
 *
 * @param texture The texture to render.
 * @param p Position where to draw the texture (global coordinates).
 * @param clip Portion of the texture to render.
 */
void GUI::Camera::draw(const Texture &texture, Position p, const SDL_Rect &clip) {
    this->draw(texture, p, clip, SDL_FLIP_NONE);
}

/**
 * @brief Draws a texture in the screen specifying the flip.
 *
 * @param texture The texture to render.
 * @param p Position where to draw the texture (global coordinates).
 * @param clip Portion of the texture to render.
 * @param flip Flip mode.
 * @param scale Scale factor of the final rendered texture size.
 */
void GUI::Camera::draw(const Texture &texture, Position p, const SDL_Rect &clip,
                       SDL_RendererFlip flip, float scale) {
    /* converts from global to local/camera coordinates */
    Position local = (p - this->cur);
    local.y *= -1;

    /* calculates the screen coordinates */
    ScreenPosition screen_local{int(local.x * this->scale), int(local.y * this->scale)};

    /* draws in screen coordinates */
    this->drawLocal(texture, screen_local, clip, flip, scale);
}

/**
 * @brief Draws a texture in the screen in camera/screen coordinates.
 * The texture is fully rendered based in it's dimensions.
 *
 * @param texture Texture to draw.
 * @param p Position where to draw it.
 */
void GUI::Camera::drawLocal(const Texture &texture, ScreenPosition p) {
    SDL_Rect clip = {0, 0, texture.getWidth(), texture.getHeight()};
    this->drawLocal(texture, p, clip);
}

/**
 * @brief Draws a texture in the screen in camera/screen coordinates.
 *
 * @param texture The texture to render.
 * @param p Position where to draw the texture (camera coordinates).
 * @param clip Portion of the texture to render.
 */
void GUI::Camera::drawLocal(const Texture &texture, ScreenPosition p, const SDL_Rect &clip) {
    this->drawLocal(texture, p, clip, SDL_FLIP_NONE);
}

/**
 * @brief Draws a texture in the screen in camera/screen coordinates specifying the flip.
 *
 * @param texture The texture to render.
 * @param p Position where to draw the texture (camera coordinates).
 * @param clip Portion of the texture to render.
 * @param flip Flip mode.
 * @param scale Scale factor of the final texture size.
 */
void GUI::Camera::drawLocal(const Texture &texture, ScreenPosition p, const SDL_Rect &clip,
                            SDL_RendererFlip flip, float scale) {
    /* calculates the scaled size */
    int w = int(clip.w * scale);
    int h = int(clip.h * scale);

    SDL_Rect dst = {};
    dst.x = p.x - w / 2;
    dst.y = p.y - h / 2;
    dst.w = w;
    dst.h = h;

    SDL_RenderCopyEx(&this->renderer, texture.get(), &clip, &dst, 0, nullptr, flip);
}
