#ifndef SpriteComponent_hpp
#define SpriteComponent_hpp

#include "../TextureManager.hpp"
#include "Animation.hpp"
#include "ECS.hpp"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_timer.h"
#include "TransformComponent.hpp"
#include <iostream>
#include <vector>

class SpriteComponent : public Component {
  private:
    TransformComponent *transform;
    SDL_Texture *texture;
    SDL_Rect srcRect, destRect;

    bool animated = false;
    SDL_RendererFlip flipTexture = SDL_FLIP_NONE;

    int currentAnimation = 0; // 0 for idle, 1 for walking, 2 for sprinting
    std::vector<Animation> animations;

  public:
    SpriteComponent(const char *path) { this->setTexture(path); }
    SpriteComponent(std::vector<Animation> animations) {
        this->animated = true;
        this->animations = animations;
    }

    ~SpriteComponent() { SDL_DestroyTexture(this->texture); }

    // used to swap texture
    void setTexture(const char *path) {
        SDL_DestroyTexture(this->texture);

        this->texture = TextureManager::LoadTexture(path);
    }

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

        if (animated) {
            // if walking in x path, meaning we have velocity on x (KeyboardController, updates the
            // x velocity when going forward or backwards, 0 velocity means its idle,
            // this->currentAnimation = this->transform->velocity.x != 0 ? 1 : 0;
            if (this->transform->velocity.x > 1.1 || this->transform->velocity.x < -1.1) {
                this->currentAnimation = 2;
                std::cout << "Sprinting!" << std::endl;
            } else if (this->transform->velocity.x > 0 || this->transform->velocity.x < 0) {
                this->currentAnimation = 1;
            } else {
                this->currentAnimation = 0;
            }

            // if negative means going backwards, positive forward
            if (this->transform->velocity.x < 0) {
                this->flipTexture = SDL_FLIP_HORIZONTAL;
            } else if (this->transform->velocity.x > 0) {
                this->flipTexture = SDL_FLIP_NONE;
            }

            Animation *animation = &this->animations.at(currentAnimation);
            this->setTexture(animation->path);

            srcRect.x = animation->frameWidth *
                        static_cast<int>((SDL_GetTicks() / animation->speed) % animation->frames);
        }

        // the rect x and y are int. and the transform are floats. these are casted automatically i
        // dont  know whether i should cast them or not, they just work like t his without issues
        // though. so i dont think i have to care about it though
        //
        // in the videos from Lets Make Games he casts it using static_cast<int>, he says its easier
        // for debug but i have no idea;

        destRect.x = transform->position.x;
        destRect.y = transform->position.y;
    }

    void draw() override {
        TextureManager::draw(this->texture, this->srcRect, this->destRect, this->flipTexture);
    }
};
#endif
