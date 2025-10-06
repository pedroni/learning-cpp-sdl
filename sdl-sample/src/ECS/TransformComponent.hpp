
#ifndef TransformComponent_hpp
#define TransformComponent_hpp

#include "../Vector2D.hpp"
#include "ECS.hpp"

class TransformComponent : public Component {
  public:
    Vector2D position;
    Vector2D velocity;

    int speed = 3;

    TransformComponent() {
        this->position.x = 0.0f;
        this->position.y = 0.0f;
    }

    TransformComponent(float x, float y) {
        this->position.x = x;
        this->position.y = y;
    }

    void init() override {
        this->velocity.x = 0.0f;
        this->velocity.y = 0.0f;
    }

    // override is useful here so that the compiler can look if the base class "Component" `update`
    // can actually be overrided, if the base class doesn't have `virtual` in the `update` method,
    // then this would fail and we would be aware that we were doing something uninteded
    void update() override {
        position.x += velocity.x * speed;
        position.y += velocity.y * speed;
    }
};
#endif
