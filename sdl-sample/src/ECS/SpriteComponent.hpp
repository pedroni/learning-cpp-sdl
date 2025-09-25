#ifndef SpriteComponent_hpp
#define SpriteComponent_hpp

#include "../TextureManager.hpp"
#include "ECS.hpp"
#include "SDL2/SDL_render.h"
#include "TransformComponent.hpp"
#include <iostream>

class SpriteComponent : public Component {
  private:
    TransformComponent *transform;
    SDL_Texture *texture;
    SDL_Rect srcRect, destRect;
    int step = 0;

  public:
    // SpriteComponent() = default;
    SpriteComponent(const char *path) { this->setTexture(path); }

    // used to swap texture
    void setTexture(const char *path) { this->texture = TextureManager::LoadTexture(path); }
    void setStep(int step) { this->step = step; }

    void init() override {
        this->transform = &entity->getComponent<TransformComponent>();

        this->srcRect.x = this->step * 128;
        this->srcRect.y = 0;

        this->srcRect.w = this->srcRect.h = 128;

        this->destRect.x = this->destRect.y = 0;
        this->destRect.w = this->destRect.h = 128;
    }

    void update() override {
        destRect.x = transform->x();
        destRect.y = transform->y();
        this->srcRect.x = this->step * 128;
    }

    void draw() override { TextureManager::draw(this->texture, this->srcRect, this->destRect); }
};
#endif
