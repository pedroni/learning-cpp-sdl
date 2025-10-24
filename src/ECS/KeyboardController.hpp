#ifndef KeyboardController_hpp
#define KeyboardController_hpp

#include "../Game.hpp"
#include "ECS.hpp"
#include "SDL2/SDL_events.h"
#include "SDL2/SDL_keyboard.h"
#include "SDL2/SDL_keycode.h"
#include "SDL2/SDL_scancode.h"
#include "TransformComponent.hpp"

class KeyboardController : public Component {
  public:
    TransformComponent *transform;
    void init() override {

        // the entity is defined on the player entity, there's a method called "addComponent" in the
        // Entity which instantiete the "KeyboardController" using generics, then after creating a
        // new object it sets the entity, see Entity::addComponent<T>();
        this->transform = &this->entity->getComponent<TransformComponent>();
    }

    void update() override {
        const Uint8 *keyboardState = SDL_GetKeyboardState(NULL);

        if (keyboardState[SDL_SCANCODE_W]) {
            this->transform->velocity.y = -1;
        }

        if (keyboardState[SDL_SCANCODE_S]) {
            this->transform->velocity.y = 1;
        }

        if (keyboardState[SDL_SCANCODE_A]) {
            this->transform->velocity.x = keyboardState[SDL_SCANCODE_LSHIFT] == 0 ? -1 : -2.2;
        }

        if (keyboardState[SDL_SCANCODE_D]) {
            this->transform->velocity.x = keyboardState[SDL_SCANCODE_LSHIFT] == 0 ? 1 : 2.2;
        }

        if (keyboardState[SDL_SCANCODE_W] == 0 && keyboardState[SDL_SCANCODE_S] == 0) {
            this->transform->velocity.y = 0;
        }

        if (keyboardState[SDL_SCANCODE_A] == 0 && keyboardState[SDL_SCANCODE_D] == 0) {
            this->transform->velocity.x = 0;
        }
    }
};

#endif
