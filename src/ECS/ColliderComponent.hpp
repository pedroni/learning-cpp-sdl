#ifndef ColliderComponent_hpp
#define ColliderComponent_hpp

#include "../Game.hpp"
#include "../TextureManager.hpp"
#include "SDL2/SDL_rect.h"
#include "SDL2/SDL_render.h"
#include "TransformComponent.hpp"

class ColliderComponent : public Component {
  public:
    SDL_Rect collider;
    std::string tag;

    SDL_Rect srcRect;
    SDL_Rect destRect;
    SDL_Texture *texture;

    TransformComponent *transform;

    ColliderComponent() {}
    ColliderComponent(std::string tag) { this->tag = tag; }
    ColliderComponent(std::string tag, int posX, int posY, int size) {
        this->tag = tag;

        collider.x = posX;
        collider.y = posY;
        collider.w = collider.h = size;
    }

    void init() override {
        if (!this->entity->hasComponent<TransformComponent>()) {
            this->entity->addComponent<TransformComponent>();
        }

        this->transform = &this->entity->getComponent<TransformComponent>();
        this->texture = TextureManager::load("assets/collision.png");
        this->srcRect = {0, 0, 32, 32};
        this->destRect = {collider.x, collider.y, collider.w, collider.h};
    }

    void update() override {
        // this should probaly be casted, because collider is int and then in the position of the
        // transform its float
        if (tag != "terrain") {
            this->collider.x = transform->position.x;
            this->collider.y = transform->position.y;

            this->collider.w = transform->width * this->transform->scale;
            this->collider.h = transform->height * this->transform->scale;
        }

        this->destRect.x = collider.x - Game::camera.x;
        this->destRect.y = collider.y - Game::camera.y;
    }

    void draw() override {
        TextureManager::draw(this->texture, this->srcRect, this->destRect, SDL_FLIP_NONE);
    }
};

#endif
