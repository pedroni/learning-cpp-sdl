#ifndef SpriteComponent_hpp
#define SpriteComponent_hpp

#include "../TextureManager.hpp"
#include "ECS.hpp"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_timer.h"
#include "TransformComponent.hpp"

class SpriteComponent : public Component {
  private:
    TransformComponent *transform;
    SDL_Texture *texture;
    SDL_Rect srcRect, destRect;

    bool animated = false;
    int frames = 0;
    int speed = 100; // in ms

  public:
    SpriteComponent(const char *path) { this->setTexture(path); }
    SpriteComponent(const char *path, int nFrames, int mSpeed) {
        this->animated = true;
        this->frames = nFrames;
        this->speed = mSpeed;
        this->setTexture(path);
    }

    ~SpriteComponent() { SDL_DestroyTexture(this->texture); }

    // used to swap texture
    void setTexture(const char *path) { this->texture = TextureManager::LoadTexture(path); }

    void init() override {
        this->transform = &entity->getComponent<TransformComponent>();

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

        if (animated) {
            srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / this->speed) % this->frames);
        }

        destRect.x = transform->position.x;
        destRect.y = transform->position.y;
    }

    void draw() override { TextureManager::draw(this->texture, this->srcRect, this->destRect); }
};
#endif
