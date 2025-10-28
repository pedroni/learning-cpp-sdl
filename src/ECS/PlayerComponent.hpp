#ifndef PlayerComponent_hpp
#define PlayerComponent_hpp

#include "ECS.hpp"
#include "SDL2/SDL_timer.h"
#include "TransformComponent.hpp"
#include <cassert>
#include <ctime>
#include <iostream>
#include <iterator>
#include <ostream>

enum PlayerState {
    IDLE,
    WALKING,
    RUNNING,
    JUMPING,
};

class PlayerComponent : public Component {
  private:
    PlayerState state_;
    TransformComponent *transform_;

  public:
    PlayerComponent() {}
    ~PlayerComponent() {}

    void init() override {
        assert(entity->hasComponent<TransformComponent>());
        transform_ = &entity->getComponent<TransformComponent>();

        state_ = IDLE;
    }

    void update() override {
        if (state_ != JUMPING) {
            if (transform_->velocity.x == -2 || transform_->velocity.x == 2) {
                state_ = RUNNING;
            } else if (transform_->velocity.x == -1 || transform_->velocity.x == 1) {
                state_ = WALKING;
            } else {
                state_ = IDLE;
            }
            previousState = state_;
        } else {
            handleJump();
        }

        std::cout << "state:" << state_ << std::endl;
    }

    PlayerState getState() { return state_; }

    void jump() { state_ = JUMPING; }

    int jumpedAt = 0;
    int jumpDuration = 500;
    PlayerState previousState;
    int jumpHeight = 100;
    int previousY = 0;

    void handleJump() {
        if (jumpedAt == 0) {
            jumpedAt = SDL_GetTicks();
            previousY = transform_->position.y;
            transform_->position.y -= jumpHeight;
        }

        if (SDL_GetTicks() - jumpedAt > jumpDuration) {
            std::cout << "STOP JUMPING" << std::endl;
            state_ = previousState;
            transform_->position.y += jumpHeight;
            jumpedAt = 0;
        }
    }
};

#endif
