#ifndef ProjectileComponent_hpp
#define ProjectileComponent_hpp

#include "../Game.hpp"
#include "../TextureManager.hpp"
#include "ECS.hpp"
#include "SDL2/SDL_rect.h"
#include "SDL2/SDL_render.h"
#include "TransformComponent.hpp"
#include <iostream>
#include <ostream>

class ProjectileComponent : public Component {
  public:
    ProjectileComponent(int range, int speed, Vector2D velocity)
        : range_(range), speed_(speed), velocity_(velocity) {}

    ~ProjectileComponent() {}

    void init() override {
        transform_ = &entity->getComponent<TransformComponent>();

        // the player component we change the velocity in the KeyboardController
        // for tihs projectile we change the velocity fixed from the projectile
        transform_->velocity = velocity_;
    }

    void update() override {
        distance_ += speed_;
        if (distance_ > range_) {
            std::cout << "fireball out of bounds" << std::endl;
            entity->destroy();
        } else if (
            // if outside the screen destroys it
            transform_->position.x > Game::camera.x + Game::camera.w ||
            transform_->position.x < Game::camera.x ||
            transform_->position.y > Game::camera.y + Game::camera.h ||
            transform_->position.y < Game::camera.y) {

            std::cout << "fireball out of screen" << std::endl;
            entity->destroy();
        }
    }

  private:
    TransformComponent *transform_;

    SDL_Texture *texture_;
    int range_ = 0;
    int speed_ = 0;
    int distance_ = 0;

    Vector2D velocity_;
};
#endif
