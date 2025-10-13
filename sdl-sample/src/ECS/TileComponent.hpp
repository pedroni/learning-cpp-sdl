#ifndef TileComponent_hpp
#define TileComponent_hpp

#include "Components.hpp"
#include "SDL2/SDL_rect.h"
#include "SpriteComponent.hpp"
#include "TransformComponent.hpp"
#include <iostream>

class TileComponent : public Component {
  public:
    SDL_Rect tileRect;
    int tileID;
    const char *path;

    TransformComponent *transform;
    SpriteComponent *sprite;

    TileComponent() {}
    TileComponent(int x, int y, int w, int h, int id) {
        this->tileRect.x = x;
        this->tileRect.y = y;
        this->tileRect.w = w;
        this->tileRect.h = h;
        this->tileID = id;

        switch (this->tileID) {
        case 0:
            this->path = "assets/water.png";
            break;
        case 1:
            this->path = "assets/dirt.png";
            break;
        case 2:
            this->path = "assets/grass.png";
            break;
        default:
            this->path = "assets/water.png";
            break;
        }
    }

    void init() override {
        this->entity
            ->addComponent<TransformComponent>(tileRect.x, tileRect.y, tileRect.w, tileRect.h, 1);

        this->transform = &this->entity->getComponent<TransformComponent>();

        this->entity->addComponent<SpriteComponent>(this->path);
        this->sprite = &this->entity->getComponent<SpriteComponent>();
    }

    void update() override {
        // this should probaly be casted, because collider is int and then in the position of the
        // transform its float
        this->tileRect.x = transform->position.x;
        this->tileRect.y = transform->position.y;

        this->tileRect.w = transform->width * this->transform->scale;
        this->tileRect.h = transform->height * this->transform->scale;
    }
};

#endif
