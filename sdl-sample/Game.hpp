//
//  Game.hpp
//  sdl-sample
//
//  Created by Lucas Pedroni on 21/09/25.
//

#ifndef Game_hpp
#define Game_hpp

#include "SDL2/SDL.h"

class Game {
public:
  Game();
  ~Game();

  void init(const char *title, int xpos, int ypos, int width, int height,
            bool fullScreen);

  void handleEvents();
  void update();
  void render();
  void clean();

  bool running();

private:
  int cnt;
  bool isRunning;
  SDL_Window *window;
  SDL_Renderer *renderer;
};

#endif /* Game_hpp */
