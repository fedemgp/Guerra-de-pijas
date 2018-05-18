#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdint.h>
#include <cassert>
#include <iostream>
#include "Exception.h"
#include "stream.h"

namespace GUI {
struct Color {
    uint8_t r, g, b;
};

class Window {
   public:
    const int width, height;

    Window() : Window(800, 600) {}
    Window(int width, int height) : width(width), height(height) {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            throw Exception{"SDL could not initialize! SDL_Error: %s", SDL_GetError()};
        }
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
            std::cerr << "Warning: Linear texture filtering not enabled!" << std::endl;
        }

        this->window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
        if (!this->window) {
            throw Exception{"Failed creating the window"};
        }

        this->surface = SDL_GetWindowSurface(this->window);
        if (!this->surface) {
            SDL_DestroyWindow(this->window);
            throw Exception{"Failed creating the screen surface"};
        }

        this->renderer = SDL_CreateRenderer(this->window, -1,
                                            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (!this->renderer) {
            SDL_DestroyWindow(this->window);
            throw Exception{"Failed creating the screen surface"};
        }

        if ((!IMG_Init(IMG_INIT_PNG)) & IMG_INIT_PNG) {
            SDL_DestroyRenderer(this->renderer);
            SDL_DestroyWindow(this->window);
            throw Exception{"Failed initialiing IMG: %s", IMG_GetError()};
        }
    }

    ~Window() {
        SDL_DestroyRenderer(this->renderer);
        SDL_DestroyWindow(this->window);
        IMG_Quit();
        SDL_Quit();
    }

    void clear() {
        SDL_SetRenderDrawColor(this->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(this->renderer);
    }

    void render() {
        SDL_RenderPresent(this->renderer);
    }

    SDL_Renderer &get_renderer() {
        return *this->renderer;
    }

   private:
    SDL_Window *window;
    SDL_Surface *surface;
    SDL_Renderer *renderer;
};

class Animation {
   public:
    Animation(const std::string &filename, SDL_Renderer &renderer, Color key) {
        /* loads the image into a temporary surface */
        SDL_Surface *tmp = IMG_Load(filename.c_str());
        if (!tmp) {
            throw Exception{"Error loading %s: %s", filename.c_str(), IMG_GetError()};
        }

        SDL_SetColorKey(tmp, SDL_TRUE, SDL_MapRGB(tmp->format, key.r, key.g, key.b));

        /* creates a texture from the surface */
        this->texture = SDL_CreateTextureFromSurface(&renderer, tmp);
        if (!this->texture) {
            SDL_FreeSurface(tmp);
            throw Exception{"Error creating texture for %s: %s", filename.c_str(), SDL_GetError()};
        }

        /* assumes the frames are squares */
        this->num_frames = tmp->h / tmp->w;
        this->size = tmp->w;

        /* releases the temporary surface */
        SDL_FreeSurface(tmp);

        assert(this->num_frames > 0);
        assert(this->size > 0);
    }
    ~Animation() {
        SDL_DestroyTexture(this->texture);
        this->texture = nullptr;
    }

    void update(float dt) {
        this->elapsed += dt;

        /* checks if the frame should be updated based on the time elapsed since the last update */
        while (this->elapsed > this->frame_rate) {
            this->advance_frame();
            this->elapsed -= this->frame_rate;
        }
    }

    void render(SDL_Renderer &renderer, int x, int y) {
        /* set rendering space and render to screen */
        SDL_Rect clip = {0, this->size * this->current_frame, this->size, this->size};
        SDL_Rect dst = {x, y, this->size, this->size};
        SDL_RenderCopyEx(&renderer, this->texture, &clip, &dst, 0, NULL, this->flip_type);
    }

    void advance_frame() {
        this->current_frame = (this->current_frame + 1) % this->num_frames;
    }

    void flip(SDL_RendererFlip flip_type) {
        this->flip_type = flip_type;
    }

   private:
    /** SDL texture of the raw image. */
    SDL_Texture *texture;
    /** Current animation frame. */
    int current_frame{0};
    /** Total number of frames in the sprite. */
    int num_frames;
    /** Size of the sprite (height and width). */
    int size;
    /** Time elapsed since last update. */
    float elapsed;
    /** Frames per seconds (should this be elsewere?). */
    float frame_rate{1.0f / 30.0f};
    SDL_RendererFlip flip_type{SDL_FLIP_NONE};
};

class Game {
   public:
    Game(Window &w)
        : window(w),
          wwalk("src/prototype/assets/img/Worms/wwalk2.png", w.get_renderer(),
                Color{0x7f, 0x7f, 0xbb}) {}
    ~Game() {}

    void start(IO::Stream<IO::GameStateMsg> *input, IO::Stream<IO::PlayerInput> *output) {
        uint32_t prev = SDL_GetTicks();
        IO::GameStateMsg m;
        bool quit = false;
        while (!quit) {
            /* handle events on queue */
            SDL_Event e;
            while (SDL_PollEvent(&e) != 0) {
                switch (e.type) {
                    case SDL_QUIT:
                        quit = true;
                        break;
                    case SDL_KEYDOWN:
                        switch (e.key.keysym.sym) {
                            case SDLK_LEFT:
                                output->push(IO::PlayerInput::move_left);
                                this->wwalk.flip(SDL_FLIP_NONE);
                                break;
                            case SDLK_RIGHT:
                                output->push(IO::PlayerInput::move_right);
                                this->wwalk.flip(SDL_FLIP_HORIZONTAL);
                                break;
                        }
                        break;
                    case SDL_KEYUP:
                        switch (e.key.keysym.sym) {
                            case SDLK_LEFT:
                            case SDLK_RIGHT:
                                output->push(IO::PlayerInput::stop_move);
                                break;
                        }
                        break;
                }
            }

            *input >> m;
            this->x = m.positions[0] * this->window.width;
            this->y = this->window.height - m.positions[1] * this->window.height;

            uint32_t current = SDL_GetTicks();
            float dt = static_cast<float>(current - prev) / 1000.0f;
            this->update(dt);
            prev = current;
            this->render();
        }
    }

    void update(float dt) {
        this->wwalk.update(dt);
    }

    void render() {
        this->window.clear();
        this->wwalk.render(this->window.get_renderer(), this->x, this->y);
        this->window.render();
    }

   private:
    Window &window;
    Animation wwalk;
    int x{0}, y{0};
};
}  // namespace GUI