

#include "TextureManager.hpp"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_render.h"

SDL_Texture *TextureManager::LoadTexture(SDL_Renderer *ren, const char *fileName) {
    SDL_Surface *tempSurface = IMG_Load(fileName);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(ren, tempSurface);

    return texture;
}
