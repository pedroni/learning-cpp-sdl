
#ifndef TransformComponent_hpp
#define TransformComponent_hpp

#include "ECS.hpp"

class TransformComponent : public Component {
  private:
    int xPos;
    int yPos;

  public:
    TransformComponent() {
        this->xPos = 0;
        this->yPos = 0;
    }

    TransformComponent(int x, int y) {
        this->xPos = x;
        this->yPos = y;
    }

    int x() const { return this->xPos; }
    int y() const { return this->yPos; }

    // override is useful here so that the compiler can look if the base class "Component" `update`
    // can actually be overrided, if the base class doesn't have `virtual` in the `update` method,
    // then this would fail and we would be aware that we were doing something uninteded
    void update() override {
        this->xPos++;
        this->yPos++;
    }

    void setPos(int x, int y) {
        this->xPos = x;
        this->yPos = y;
    }
};
#endif
