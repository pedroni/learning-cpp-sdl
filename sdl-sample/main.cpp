//
//  main.cpp
//  sdl-sample
//
//  Created by Lucas Pedroni on 21/09/25.
//
#include "Game.hpp"
#include "iostream"

Game *game = NULL;

int main(int argc, const char *argv[]) {
  std::cout << "Hello, World!\n";
  game = new Game();
  game->init("Game Engine", 0, 0, 800, 600, false);
  std::cout << "hahaha" << std::endl;

  while (game->running()) {
    game->handleEvents();
    game->update();
    game->render();
  }

  game->clean();

  return EXIT_SUCCESS;
}
