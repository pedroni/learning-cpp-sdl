
#include <array>
#include <bitset>
#include <cstddef>
#include <iostream>
#include <memory>
#include <vector>

#ifndef ECS_hpp
#define ECS_hpp

// Entity Component System
class Component;
class Entity;

using ComponentID = std::size_t;

inline ComponentID getComponentTypeID() {
    // marking this variable as static means that the value will be remembered between function
    // calls if we were to remove static the last id would be destroyed after every function call
    // and the memory would be clean up. using static with an inline function makes the variable
    // value available for subsequent calls
    //
    // ------------
    //
    // every time this is called it increments the lastId
    // note that this one doesn't have a template<typename T> therefore if you call without a
    // template it will always increment the ID. when using a template the ID will not be
    // incremented

    static ComponentID lastID = 0;
    return lastID++;
}

template <typename T>
inline ComponentID getComponentTypeID() {
    // ⚠️ in here the id is not incremented. it retrieves the available of typename T
    // so if we call
    // take these calls for example:
    // getComponentTypeID<First>(); <- returns 0
    // getComponentTypeID<First>(); <- returns 0 // same value as before because of T
    // getComponentTypeID<Second>(); <- returns 1 a different T
    static ComponentID typeID = getComponentTypeID();
    return typeID;
}

// max amount of things that our Entity Component System (ECS) can hold
constexpr std::size_t maxComponents = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using ComponentArray = std::array<Component *, maxComponents>;

// this works like interface beaucse there's no implementation at all and all function are virtual,
// which allows us to override them in the actual implementation
class Component {
  public:
    Entity *entity;
    // the virtual keyword allows polymorphism, allows derived classes that extends the base class
    // to override the original class implmenentation
    virtual void init() {}
    virtual void update() {}
    virtual void draw() {}

    virtual ~Component() {}
};

class Entity {
  private:
    // when false remove from the game
    bool active = true;

    // vector is an array with dynamic size
    std::vector<std::unique_ptr<Component>> components;

    ComponentArray componentArray;

    // this is used in order to check if a component has been registered or not, its much faster
    // than checking the array index and then checking if the pointer is NULL if we were to do
    // if(componentArray[0] == NULL) this is much slower because a memory for a pointers. accessing
    // the componentArray requires looking up 8 bytes of memory (the size of a pointer) now checking
    // if(componentBitSet[0] == true) only requires checking 1 bit of memory (the size of a bit) in
    // our case we have a max component size set for 32, therefore the whole size of our set is
    // 32bits (4 bytes), if we were checking pointers it would be 256 bytes, 64x times bigger.
    ComponentBitSet componentBitSet;

  public:
    void update() {
        for (std::size_t i = 0; i < this->components.size(); i++) {
            components[i]->update();
        }
        for (std::size_t i = 0; i < this->components.size(); i++) {
            components[i]->draw();
        }
    }

    void draw() {}

    // const means that we're promising that this function will not modify the state
    bool isActive() const { return this->active; }

    // this function doesnt have the const keyword, therefore it can (and will) modify the state
    void destroy() { this->active = false; }

    template <typename T>
    bool hasComponent() const {
        return componentBitSet[getComponentTypeID<T>()];
    }

    template <typename T, typename... TArgs>
    T &addComponent(TArgs &&...mArgs) {
        T *newTypedComponent = new T(std::forward<TArgs>(mArgs)...);

        newTypedComponent->entity = this;
        std::unique_ptr<Component> uPtr{newTypedComponent};

        components.emplace_back(std::move(uPtr));

        componentArray[getComponentTypeID<T>()] = newTypedComponent;
        componentBitSet[getComponentTypeID<T>()] = true;

        newTypedComponent->init();

        return *newTypedComponent;
    }

    template <typename T>
    T &getComponent() const {
        Component *ptr = componentArray[getComponentTypeID<T>()];
        return *static_cast<T *>(ptr);
    }
};

class Manager {
  private:
    std::vector<std::unique_ptr<Entity>> entities;

  public:
    void update() {
        for (size_t i = 0; i < entities.size(); i++) {
            entities[i]->update();
        }
    }

    void draw() {
        for (size_t i = 0; i < entities.size(); i++) {
            entities[i]->draw();
        }
    }

    void refresh() {
        // erase takes two arguments: start and end
        // e.g. [0, 1, 2, 3, 4]
        // entities.erase(0, 2) // [3,4]
        //
        // remove_if takes 3 arguments, begin of iterator, end of iterator and a lambda function
        // that validates whether the thing should be removed or not.
        // ⚠️ note that: remove_if returns a "new end", remove_if just rearranges the elements of the
        // vector putting all elements that should be removed at the end, so this is used in
        // combination with .erase, it is the first arg of erase and the second arg is the the end
        // of the vector

        entities.erase(std::remove_if(entities.begin(),
                                      entities.end(),
                                      [](const std::unique_ptr<Entity> &mEntity) {
                                          return !mEntity->isActive();
                                      }),
                       entities.end());
    }

    Entity &addEntity() {
        Entity *entity = new Entity();
        std::unique_ptr<Entity> uPtr{entity};
        entities.emplace_back(std::move(uPtr));
        return *entity;
    }
};

#endif
