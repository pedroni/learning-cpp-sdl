#ifndef ColliderComponent_hpp
#define ColliderComponent_hpp

#include "../Game.hpp"
#include "../TextureManager.hpp"
#include "SDL2/SDL_rect.h"
#include "SDL2/SDL_render.h"
#include "TransformComponent.hpp"
#include <cassert>

class ColliderComponent : public Component {
  public:
    SDL_Rect collider;
    std::string tag;

    SDL_Rect srcRect;
    SDL_Rect destRect;

    SDL_Texture *texture;

    TransformComponent *transform;

    int offsetX, offsetY;

    ColliderComponent() {}
    ColliderComponent(std::string tag) {
        this->tag = tag;
        collider = {0, 0, 0, 0};
    }

    // todo: implement offset position, this will be useful for sprites (transform component) that
    // arent actually shaped exactly like the collider
    ColliderComponent(std::string tag, int width, int height, int offsetX, int offsetY) {
        this->tag = tag;
        this->offsetX = offsetX;
        this->offsetY = offsetY;

        collider = {0, 0, width, height};
    }

    void init() override {
        assert(this->entity->hasComponent<TransformComponent>());

        this->transform = &this->entity->getComponent<TransformComponent>();

        // its different than 0 when we have a collider that doesn't exactly match the size of
        // TransformComponent, for example our player when launching skills is 128px wide, but his
        // body is only 64px wide
        if (this->collider.w == 0 || this->collider.h == 0) {
            // when dimensions arent provided by constructor we take from the TransformComponent
            this->collider.w = transform->width * this->transform->scale;
            this->collider.h = transform->height * this->transform->scale;
        }

        this->texture = TextureManager::load("assets/collision.png");
        this->srcRect = {0, 0, 32, 32};

        this->destRect = {collider.x, collider.y, collider.w, collider.h};
    }

    void update() override {
        this->collider.x = offsetX + transform->position.x;
        this->collider.y = offsetY + transform->position.y;

        this->destRect.x = collider.x - Game::camera.x;
        this->destRect.y = collider.y - Game::camera.y;
    }

    void draw(double alpha) override {
        // comment this out to remove the debug texture
        TextureManager::draw(this->texture, this->srcRect, this->destRect, SDL_FLIP_NONE);
    }
};

#endif
