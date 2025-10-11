#ifndef ColliderComponent_hpp
#define ColliderComponent_hpp

#include "../Game.hpp"
#include "SDL2/SDL_rect.h"
#include "TransformComponent.hpp"

class ColliderComponent : public Component {
  public:
    SDL_Rect collider;
    std::string tag;

    TransformComponent *transform;

    ColliderComponent() {}
    ColliderComponent(std::string tag) { this->tag = tag; }

    void init() override {
        if (!this->entity->hasComponent<TransformComponent>()) {
            this->entity->addComponent<TransformComponent>();
        }

        this->transform = &this->entity->getComponent<TransformComponent>();

        Game::colliders.push_back(this);
    }

    void update() override {
        // this should probaly be casted, because collider is int and then in the position of the
        // transform its float
        this->collider.x = transform->position.x;
        this->collider.y = transform->position.y;

        this->collider.w = transform->width * this->transform->scale;
        this->collider.h = transform->height * this->transform->scale;
    }
};

#endif
