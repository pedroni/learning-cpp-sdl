

#include "TextureManager.hpp"
#include "Game.hpp"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_surface.h"

SDL_Texture *TextureManager::load(const char *fileName) {
    SDL_Surface *tempSurface = IMG_Load(fileName);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);

    SDL_FreeSurface(tempSurface);
    return texture;
}

void TextureManager::draw(
    SDL_Texture *texture,
    SDL_Rect src,
    SDL_Rect dest,
    SDL_RendererFlip flip) {
    SDL_RenderCopyEx(Game::renderer, texture, &src, &dest, 0, NULL, flip);
}
