

#include "ECS.hpp"

void Entity::addGroup(Group group) {
    // std::cout << "calling add group:" << group << std::endl;
    this->groupBitset[group] = true;
    this->manager.addToGroup(this, group);
};
