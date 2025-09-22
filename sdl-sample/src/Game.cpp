#include "Game.hpp"
#include "SDL2/SDL.h"
#include "TextureManager.hpp"
#include <cmath>
#include <iostream>

SDL_Texture *playerTexture;
SDL_Rect srcR, destR;

SDL_Texture *bg1Texture;
SDL_Rect bg1SrcR, bg1DestR;

SDL_Texture *bg2Texture;
SDL_Rect bg2SrcR, bg2DestR;

SDL_Texture *bg3Texture;
SDL_Rect bg3SrcR, bg3DestR;

SDL_Texture *bg4Texture;
SDL_Rect bg4SrcR, bg4DestR;

SDL_Texture *bg5Texture;
SDL_Rect bg5SrcR, bg5DestR;

SDL_Texture *bg6Texture;
SDL_Rect bg6SrcR, bg6DestR;

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

    bg1Texture = TextureManager::LoadTexture(
        this->renderer, "assets/Battleground1/Pale/sky.png");
    bg1DestR.x = -800;

    bg2Texture = TextureManager::LoadTexture(
        this->renderer, "assets/Battleground1/Pale/ruins_bg.png");

    bg3Texture = TextureManager::LoadTexture(
        this->renderer, "assets/Battleground1/Pale/hills&trees.png");

    bg4Texture = TextureManager::LoadTexture(
        this->renderer, "assets/Battleground1/Pale/ruins.png");

    bg5Texture = TextureManager::LoadTexture(
        this->renderer, "assets/Battleground1/Pale/ruins2.png");

    bg6Texture = TextureManager::LoadTexture(
        this->renderer, "assets/Battleground1/Pale/stones&grass.png");

    playerTexture =
        TextureManager::LoadTexture(this->renderer, "assets/Knight_1/Walk.png");
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
    std::cout << "frame: " << cnt << std::endl;
    destR.w = 128 * 2;
    destR.h = 128 * 2;

    srcR.w = 128;
    srcR.h = 128;
    int step = floor(cnt / 15);
    srcR.x = (step % 8) * 128;

    if (cnt > 960) {
        cnt = -156;
    }

    destR.y = 260;
    destR.x = cnt;

    bg1DestR.w = 1600;
    bg1DestR.h = 600;
    if (bg1DestR.x > 0) {
        bg1DestR.x = -800;
    } else {
        bg1DestR.x += 1;
    }

    bg2DestR.w = 800;
    bg2DestR.h = 600;
    bg2DestR.x = 0;

    bg3DestR.w = 800;
    bg3DestR.h = 600;
    bg3DestR.x = 0;

    bg4DestR.w = 800;
    bg4DestR.h = 600;
    bg4DestR.x = 0;

    bg5DestR.w = 800;
    bg5DestR.h = 600;
    bg5DestR.x = 0;

    bg6DestR.w = 800;
    bg6DestR.h = 600;
    bg6DestR.x = 0;
}

void Game::render() {
    SDL_RenderClear(this->renderer);
    // this is where you render stuff, images, sprites

    SDL_RenderCopy(this->renderer, bg1Texture, NULL, &bg1DestR);
    SDL_RenderCopy(this->renderer, bg2Texture, NULL, &bg2DestR);
    SDL_RenderCopy(this->renderer, bg3Texture, NULL, &bg3DestR);
    SDL_RenderCopy(this->renderer, bg4Texture, NULL, &bg4DestR);
    SDL_RenderCopy(this->renderer, bg5Texture, NULL, &bg5DestR);
    SDL_RenderCopy(this->renderer, bg6Texture, NULL, &bg6DestR);

    SDL_RenderCopy(this->renderer, playerTexture, &srcR, &destR);

    SDL_RenderPresent(this->renderer);
}

void Game::clean() {
    SDL_DestroyWindow(this->window);
    SDL_DestroyRenderer(this->renderer);
    SDL_Quit();
    std::cout << "Game Cleaned" << std::endl;
}

bool Game::running() { return this->isRunning; }
