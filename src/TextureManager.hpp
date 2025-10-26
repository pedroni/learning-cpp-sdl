
#ifndef TextureManager_hpp
#define TextureManager_hpp

#include "SDL2/SDL_rect.h"
#include "SDL2/SDL_render.h"

class TextureManager {
  public:
    static SDL_Texture *load(const char *fileName);
    static void draw(SDL_Texture *texture, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip);
};

#endif
