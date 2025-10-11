#ifndef SpriteComponent_hpp
#define SpriteComponent_hpp

#include "../TextureManager.hpp"
#include "ECS.hpp"
#include "SDL2/SDL_render.h"
#include "TransformComponent.hpp"

class SpriteComponent : public Component {
  private:
    TransformComponent *transform;
    SDL_Texture *texture;
    SDL_Rect srcRect, destRect;
    int step = 0;

  public:
    // SpriteComponent() = default;
    SpriteComponent(const char *path) { this->setTexture(path); }

    ~SpriteComponent() { SDL_DestroyTexture(this->texture); }

    // used to swap texture
    void setTexture(const char *path) { this->texture = TextureManager::LoadTexture(path); }
    void setStep(int step) { this->step = step; }

    void init() override {
        this->transform = &entity->getComponent<TransformComponent>();

        this->srcRect.x = this->step * 128;
        this->srcRect.y = 0;

        this->srcRect.w = this->transform->width;
        this->srcRect.h = this->transform->height;

        this->destRect.x = this->destRect.y = 0;

        this->destRect.w = this->transform->width * this->transform->scale;
        this->destRect.h = this->transform->height * this->transform->scale;
    }

    void update() override {
        // the rect x and y are int. and the transform are floats. these are casted automatically i
        // dont  know whether i should cast them or not, they just work like t his without issues
        // though. so i dont think i have to care about it though
        //
        // in the videos from Lets Make Games he casts it using static_cast<int>, he says its easier
        // for debug but i have no idea;

        destRect.x = transform->position.x;
        destRect.y = transform->position.y;
        this->srcRect.x = this->step * 128;
    }

    void draw() override { TextureManager::draw(this->texture, this->srcRect, this->destRect); }
};
#endif
