#ifndef SpriteComponent_hpp
#define SpriteComponent_hpp

#include "../TextureManager.hpp"
#include "ECS.hpp"
#include "PositionComponent.hpp"
#include "SDL2/SDL_render.h"
#include <iostream>

class SpriteComponent : public Component {
  private:
    PositionComponent *position;
    SDL_Texture *texture;
    SDL_Rect srcRect, destRect;

  public:
    SpriteComponent() = default;
    SpriteComponent(const char *path) { this->texture = TextureManager::LoadTexture(path); }

    void init() override {
        this->position = &entity->getComponent<PositionComponent>();

        this->srcRect.x = this->srcRect.y = 0;
        this->srcRect.w = this->srcRect.h = 128;

        this->destRect.x = this->destRect.y = 0;
        this->destRect.w = this->destRect.w = 256;
    }

    void update() override {
        destRect.x = position->x();
        destRect.y = position->y();
    }

    void draw() override { TextureManager::draw(this->texture, this->srcRect, this->destRect); }
};
#endif
