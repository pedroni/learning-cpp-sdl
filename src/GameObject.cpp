#include "GameObject.hpp"

#include "Game.hpp"
#include "SDL2/SDL_render.h"
#include "TextureManager.hpp"

GameObject::GameObject(const char *texturesheet, int x, int y) {
    this->texture = TextureManager::LoadTexture(texturesheet);
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
    SDL_RenderCopy(Game::renderer, this->texture, &this->srcRect, &this->destRect);
}
