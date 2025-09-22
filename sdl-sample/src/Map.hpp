
#ifndef Map_hpp
#define Map_hpp

#include "SDL2/SDL_rect.h"
#include "SDL2/SDL_render.h"
class Map {
  public:
    Map();
    ~Map();

    void load(int arr[20][25]);
    void draw();

  private:
    SDL_Rect src, dest;

    SDL_Texture *dirt;
    SDL_Texture *grass;
    SDL_Texture *water;

    int map[20][25];
};

#endif
