
#include "Collision.hpp"
#include "SDL2/SDL_rect.h"

bool Collision::AABB(const SDL_Rect &A, const SDL_Rect &B) {
    bool xOverlap = A.x + A.w >= B.x && B.x + B.w >= A.x;
    bool yOverlap = A.y + A.h >= B.y && B.y + B.h >= A.y;

    if (xOverlap && yOverlap) {
        return true;
    }

    return false;
}
