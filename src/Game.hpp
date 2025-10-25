
#ifndef Game_hpp
#define Game_hpp

#include "SDL2/SDL_events.h"
#include "SDL2/SDL_render.h"
#include <vector>

class ColliderComponent;

class Game {
  public:
    Game();
    ~Game();

    void init(const char *title, int xpos, int ypos, int width, int height, bool fullScreen);

    void handleEvents();
    void update();
    void render();
    void clean();

    bool running();

    // Declare as static so we can use it globally as a singleton once it is initialized
    // In TextureManager, GameObject and any other place that we have to use we can simply do
    // Game::renderer instead of having to delcare multiple renderer pointers everywhere

    static void addTile(int srcX, int srcY, int posX, int posY);
    static SDL_Renderer *renderer;
    static SDL_Event *event;

    static std::vector<ColliderComponent *> colliders;

  private:
    int cnt;
    bool isRunning;
    SDL_Window *window;
};

#endif /* Game_hpp */
