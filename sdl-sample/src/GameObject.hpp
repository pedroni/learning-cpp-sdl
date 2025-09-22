#include "SDL2/SDL_render.h"

class GameObject {
  public:
    GameObject(const char *texturesheet, int x = 0, int y = 0);
    ~GameObject();

    void update();
    void render();

  private:
    int xPos;
    int yPos;

    SDL_Texture *texture;
    SDL_Rect srcRect, destRect;

    SDL_Renderer *renderer;
};
