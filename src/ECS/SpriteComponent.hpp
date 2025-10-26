#ifndef SpriteComponent_hpp
#define SpriteComponent_hpp

#include "../Game.hpp"
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
    SDL_Rect srcRect, destRect;

    SDL_RendererFlip flipTexture = SDL_FLIP_NONE;

    int currentAnimation = 0; // 0 for idle, 1 for walking, 2 for sprinting
    std::vector<Animation> animations;

    std::vector<SDL_Texture *> textures;
    SDL_Texture *currentTexture;

  public:
    SpriteComponent(const std::vector<Animation> &animations) { this->animations = animations; }

    ~SpriteComponent() {
        for (int i = 0; i < textures.size(); i++) {
            SDL_DestroyTexture(textures[i]);
        }
    }

    void init() override {
        this->transform = &entity->getComponent<TransformComponent>();

        for (int i = 0; i < animations.size(); i++) {
            this->textures.push_back(TextureManager::LoadTexture(animations[i].path));
        }

        this->srcRect.y = 0;

        this->srcRect.w = this->transform->width;
        this->srcRect.h = this->transform->height;

        this->destRect.x = this->destRect.y = 0;

        this->destRect.w = this->transform->width * this->transform->scale;
        this->destRect.h = this->transform->height * this->transform->scale;
    }

    void update() override {
        // if walking in x path, meaning we have velocity on x (KeyboardController, updates the
        // x velocity when going forward or backwards, 0 velocity means its idle,
        // this->currentAnimation = this->transform->velocity.x != 0 ? 1 : 0;
        if (this->transform->velocity.x > 1.1 || this->transform->velocity.x < -1.1) {
            this->currentAnimation = 2;
            // std::cout << "Sprinting!" << std::endl;
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

        Animation &animation = this->animations.at(currentAnimation);
        this->currentTexture = textures.at(currentAnimation);

        srcRect.x = animation.frameWidth *
                    static_cast<int>((SDL_GetTicks() / animation.speed) % animation.frames);

        // the position.x and position.y from transform is moved on the KeyboardController, they're
        // modified whenever WASD are pressed. The camera x and y are used as offsets so that we can
        // always make the player be at the center of the screen. note that destRect is where in the
        // window (renderer) we will be placing our player image (sprite)
        destRect.x = transform->position.x - Game::camera.x;
        destRect.y = transform->position.y - Game::camera.y;
    }

    void draw() override {
        TextureManager::draw(
            this->currentTexture,
            this->srcRect,
            this->destRect,
            this->flipTexture);
    }
};
#endif
