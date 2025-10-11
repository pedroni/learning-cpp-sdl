
#ifndef Collision_hpp
#define Collision_hpp

#include "SDL2/SDL_rect.h"
class Collision {
  public:
    /** AABB stands for axis-aligned bounding box */
    static bool AABB(const SDL_Rect &A, const SDL_Rect &B);
};

#endif
