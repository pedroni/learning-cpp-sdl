#include "Game.hpp"
#include "SDL2/SDL_timer.h"

Game *game = NULL;

int main(int argc, const char *argv[]) {
    game = new Game();
    game->init("Pedroni Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
               800, 600, false);

    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    while (game->running()) {
        frameStart = SDL_GetTicks();

        game->handleEvents();
        game->update();
        game->render();

        // check how much time it takes in milliseconds to update our objects
        // and rendering it in the screen
        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime) {
            // if the game updated to fast we delay it a bit to that the frames
            // are in sync e.g. frameDelay is 16ms, and our frameTime was 10ms,
            // our  we delay it by 6ms
            SDL_Delay(frameDelay - frameTime);
        }
    }

    game->clean();

    return EXIT_SUCCESS;
}
