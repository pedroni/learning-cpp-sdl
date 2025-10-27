
#include "Collision.hpp"
#include "ECS/ColliderComponent.hpp"
#include "SDL2/SDL_rect.h"
#include <iostream>

bool Collision::AABB(const SDL_Rect &A, const SDL_Rect &B) {
    bool xOverlap = A.x + A.w > B.x && B.x + B.w > A.x;
    bool yOverlap = A.y + A.h > B.y && B.y + B.h > A.y;

    if (xOverlap && yOverlap) {
        return true;
    }

    return false;
}

bool Collision::AABB(const ColliderComponent &A, const ColliderComponent &B) {
    if (&A != &B && AABB(A.collider, B.collider)) {
        std::cout << A.tag << " hits : " << B.tag << std::endl;
        return true;
    }

    return false;
}
