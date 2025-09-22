

#include "TextureManager.hpp"
#include "Game.hpp"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_render.h"

SDL_Texture *TextureManager::LoadTexture(const char *fileName) {
    SDL_Surface *tempSurface = IMG_Load(fileName);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);

    return texture;
}

void TextureManager::draw(SDL_Texture *texture, SDL_Rect src, SDL_Rect dest) {
    SDL_RenderCopy(Game::renderer, texture, &src, &dest);
}
