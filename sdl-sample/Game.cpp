//
//  Game.cpp
//  sdl-sample
//
//  Created by Lucas Pedroni on 21/09/25.
//

#include "Game.hpp"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_rect.h"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_surface.h"
#include <iostream>

SDL_Texture *playerTexture;
SDL_Rect srcR, destR;

Game::Game() {}
Game::~Game() {}

void Game::init(const char *title, int xpos, int ypos, int width, int height,
                bool fullScreen) {
    int flags = 0;
    if (fullScreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "Subsystems initialised!" << std::endl;
        this->window =
            SDL_CreateWindow(title, xpos, ypos, width, height, flags);

        if (this->window) {
            std::cout << "Window created!" << std::endl;
        }

        this->renderer = SDL_CreateRenderer(this->window, -1, 0);

        if (this->renderer) {
            SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);
            std::cout << "Renderer created!" << std::endl;
        }

        this->isRunning = true;
    } else {
        this->isRunning = false;
    }
    SDL_Surface *tempSurface = IMG_Load("assets/vest.png");

    playerTexture = SDL_CreateTextureFromSurface(this->renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
}

void Game::handleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
    case SDL_QUIT:
        isRunning = false;
        break;

    default:
        break;
    }
}

void Game::update() {
    cnt++;
    destR.w = 64;
    destR.h = 64;
    if (cnt > 864) {
        cnt = -64;
    }
    destR.x = cnt;
}

void Game::render() {
    SDL_RenderClear(this->renderer);
    // this is where you render stuff, images, sprites

    SDL_RenderCopy(this->renderer, playerTexture, NULL, &destR);

    SDL_RenderPresent(this->renderer);
}

void Game::clean() {
    SDL_DestroyWindow(this->window);
    SDL_DestroyRenderer(this->renderer);
    SDL_Quit();
    std::cout << "Game Cleaned" << std::endl;
}

bool Game::running() { return this->isRunning; }
