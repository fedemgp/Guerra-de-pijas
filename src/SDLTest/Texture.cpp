/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 12/05/18
 */

#include <Exception.h>
#include "Texture.h"

Texture::Texture() : texture(nullptr), width(0), height(0){}

Texture::~Texture(){
    this->free();
}

void Texture::loadFromFile(const char *path, SDL_Renderer *renderer, Uint8 r,
                           Uint8 g, Uint8 b){
    //Get rid of preexisting texture
    this->free();

    //load img at specified path
    SDL_Surface *loadedSurface = IMG_Load(path);
    if (loadedSurface == nullptr){
        throw Exception("Unable to load image %s! SDL_image Error:%s\n", path,
                        IMG_GetError());
    }

    //Color key image
    SDL_SetColorKey(loadedSurface, SDL_TRUE,
                    SDL_MapRGB(loadedSurface->format, r, g, b));

    //Create texture from surface pixls
    this->texture = SDL_CreateTextureFromSurface(renderer,
                                                 loadedSurface);
    if (this->texture == nullptr){
        throw Exception("Unable to create texture from %s! SDL Error: %s\n",
                        path, SDL_GetError());
    }
    //Get image dimensions
    this->width = loadedSurface->w;
    this->height = loadedSurface->h;

    //Get rid of old loaded surface
    SDL_FreeSurface(loadedSurface);
}

void Texture::free(){
    if (this->texture != nullptr){
        SDL_DestroyTexture(this->texture);
        this->texture = nullptr;
        this->width = 0;
        this->height = 0;
    }
}

void Texture::setColor(Uint8 red, Uint8 green, Uint8 blue){
    //Modulate texture
    SDL_SetTextureColorMod(this->texture, red, green, blue);
}

void Texture::setBlendMode(SDL_BlendMode blending){
    //Set blending function
    SDL_SetTextureBlendMode(this->texture, blending);
}

void Texture::setAlpha(Uint8 alpha){
    //Modulate texture alpha
    SDL_SetTextureAlphaMod(this->texture, alpha);
}

void Texture::render(int x, int y, SDL_Renderer *renderer, SDL_Rect *clip,
                     double angle, SDL_Point *center, SDL_RendererFlip flip){
    //Set rendering space and render to screen
    SDL_Rect renderQuad = {x, y, this->width, this->height};

    //Set clip rendering dimensions
    if (clip != nullptr){
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    SDL_RenderCopyEx(renderer, this->texture, clip, &renderQuad, angle, center,
                     flip);
}

int Texture::getHeight(){
    return this->height;
}

int Texture::getWidth(){
    return this->width;
}