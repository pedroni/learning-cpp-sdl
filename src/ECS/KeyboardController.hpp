#ifndef KeyboardController_hpp
#define KeyboardController_hpp

#include "../Game.hpp"
#include "ECS.hpp"
#include "PlayerComponent.hpp"
#include "SDL2/SDL_keyboard.h"
#include "SDL2/SDL_scancode.h"
#include "TransformComponent.hpp"
#include <cassert>

class KeyboardController : public Component {
  private:
    TransformComponent *transform_;
    PlayerComponent *player_;

  public:
    void init() override {
        assert(entity->hasComponent<TransformComponent>());
        assert(entity->hasComponent<PlayerComponent>());

        // the entity is defined on the player entity, there's a method called "addComponent" in the
        // Entity which instantiete the "KeyboardController" using generics, then after creating a
        // new object it sets the entity, see Entity::addComponent<T>();
        transform_ = &this->entity->getComponent<TransformComponent>();
        player_ = &this->entity->getComponent<PlayerComponent>();
    }

    void update() override {
        const Uint8 *keyboardState = SDL_GetKeyboardState(NULL);

        if (player_->getState() != JUMPING) {
            if (keyboardState[SDL_SCANCODE_SPACE]) {

                player_->jump();
                return;
            }

            if (keyboardState[SDL_SCANCODE_A]) {
                transform_->velocity.x = keyboardState[SDL_SCANCODE_LSHIFT] == 0 ? -1 : -2;
            }

            if (keyboardState[SDL_SCANCODE_D]) {
                transform_->velocity.x = keyboardState[SDL_SCANCODE_LSHIFT] == 0 ? 1 : 2;
            }

            if (keyboardState[SDL_SCANCODE_A] == 0 && keyboardState[SDL_SCANCODE_D] == 0) {
                transform_->velocity.x = 0;
            }
        }

        if (keyboardState[SDL_SCANCODE_ESCAPE]) {
            Game::isRunning = false;
        }
    }
};

#endif
