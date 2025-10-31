#include "Game.hpp"
#include "SDL2/SDL_timer.h"
#include <iostream>
#include <ostream>

Game *game = NULL;

int main(int argc, const char *argv[]) {
    game = new Game();
    game->init("Pedroni Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);

    const int heartbeat = 60;
    const int frameDelay = 1000 / heartbeat;

    unsigned int previous = SDL_GetTicks();
    double lag = 0;

    while (game->running()) {
        unsigned int current = SDL_GetTicks();
        unsigned int elapsed = current - previous;
        previous = current;
        lag += elapsed;

        game->handleEvents();
        while (lag >= frameDelay) {
            game->update();
            lag -= frameDelay;
        }

        double alpha = lag / frameDelay;
        game->render(alpha);
    }

    game->clean();

    return EXIT_SUCCESS;
}
