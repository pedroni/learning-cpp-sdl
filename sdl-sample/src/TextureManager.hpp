
#ifndef TextureManager_hpp
#define TextureManager_hpp

#include "SDL2/SDL_render.h"

class TextureManager {
  public:
    static SDL_Texture *LoadTexture(SDL_Renderer *ren, const char *fileName);
};

#endif
