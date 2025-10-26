
#ifndef Map_hpp
#define Map_hpp

#include "SDL2/SDL_render.h"
#include <string>
class Map {
  public:
    Map(const char *texturePath,
        std::string coordinatesPath,
        int sizeX,
        int sizeY,
        int tileSize,
        int mapScale);
    void render();

  private:
    SDL_Texture *texture;
    std::string coordinatesPath;
    int sizeX;
    int sizeY;
    int tileSize;
    int mapScale;
    int scaledSize;

    void addTile(int srcX, int srcY, int posX, int posY);
};

#endif
