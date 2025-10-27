#ifndef SpriteComponent_hpp
#define SpriteComponent_hpp

#include "../Game.hpp"
#include "../TextureManager.hpp"
#include "Animation.hpp"
#include "ECS.hpp"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_timer.h"
#include "TransformComponent.hpp"
#include <vector>

class SpriteComponent : public Component {
  private:
    TransformComponent *transform;
    SDL_Rect srcRect, destRect;

    SDL_RendererFlip flipTexture = SDL_FLIP_NONE;

    // index for each expected animation 0 for idle, 1 for walking, 2 for sprinting, TODO: add a
    // map? add a tag for each animation?
    std::vector<Animation> animations;

    Animation currentAnimation;

    bool movingCharacter = false;

  public:
    SpriteComponent(const std::vector<Animation> &animations) {
        this->animations = animations;
        this->movingCharacter = true;
    }

    SpriteComponent(const Animation &animation) { this->animations.push_back(animation); }

    void init() override {
        this->transform = &entity->getComponent<TransformComponent>();
        this->currentAnimation = this->animations.at(0);

        this->srcRect.y = 0;

        this->srcRect.w = this->transform->width;
        this->srcRect.h = this->transform->height;

        this->destRect.x = this->destRect.y = 0;

        this->destRect.w = this->transform->width * this->transform->scale;
        this->destRect.h = this->transform->height * this->transform->scale;
    }

    void update() override {
        if (this->movingCharacter) {
            // if walking in x path, meaning we have velocity on x (KeyboardController, updates the
            // x velocity when going forward or backwards, 0 velocity means its idle,
            // this->currentAnimation = this->transform->velocity.x != 0 ? 1 : 0;
            if (this->transform->velocity.x > 1.1 || this->transform->velocity.x < -1.1) {
                this->currentAnimation = this->animations.at(2);
                // std::cout << "Sprinting!" << std::endl;
            } else if (this->transform->velocity.x > 0 || this->transform->velocity.x < 0) {
                this->currentAnimation = this->animations.at(1);
            } else {
                this->currentAnimation = this->animations.at(0);
            }

            // if negative means going backwards, positive forward
            if (this->transform->velocity.x < 0) {
                this->flipTexture = SDL_FLIP_HORIZONTAL;
            } else if (this->transform->velocity.x > 0) {
                this->flipTexture = SDL_FLIP_NONE;
            }
        }

        srcRect.x =
            this->currentAnimation.frameWidth *
            static_cast<int>(
                (SDL_GetTicks() / this->currentAnimation.speed) % this->currentAnimation.frames);

        // the position.x and position.y from transform is moved on the KeyboardController, they're
        // modified whenever WASD are pressed. The position is where the player is actually in the
        // world.
        //
        // The camera x and y are used as offsets so that we can always make the player be at the
        // center of the screen. note that destRect is where in the window (renderer) we will be
        // placing our player image (sprite)
        destRect.x = transform->position.x - Game::camera.x;
        destRect.y = transform->position.y - Game::camera.y;
    }

    void draw() override {
        TextureManager::draw(
            this->currentAnimation.texture,
            this->srcRect,
            this->destRect,
            this->flipTexture);
    }
};
#endif
