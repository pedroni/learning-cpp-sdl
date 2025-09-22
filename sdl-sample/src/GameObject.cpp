#include "GameObject.hpp"

#include "SDL2/SDL_render.h"
#include "TextureManager.hpp"

GameObject::GameObject(SDL_Renderer *ren, const char *texturesheet, int x, int y) {
    this->renderer = ren;
    this->texture = TextureManager::LoadTexture(this->renderer, texturesheet);
    this->xPos = x;
    this->yPos = y;
}

GameObject::~GameObject() {}

void GameObject::update() {
    xPos = 0;
    yPos = 0;

    srcRect.w = 128;
    srcRect.h = 128;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.x = xPos;
    destRect.y = yPos;
    destRect.w = srcRect.w * 1;
    destRect.h = srcRect.h * 1;
}
void GameObject::render() {
    SDL_RenderCopy(this->renderer, this->texture, &this->srcRect, &this->destRect);
}
