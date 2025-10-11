#include "Game.hpp"
#include "Collision.hpp"
#include "ECS/ColliderComponent.hpp"
#include "ECS/Components.hpp"
#include "ECS/ECS.hpp"
#include "ECS/KeyboardController.hpp"
#include "ECS/SpriteComponent.hpp"
#include "ECS/TileComponent.hpp"
#include "ECS/TransformComponent.hpp"
#include "Map.hpp"
#include "SDL2/SDL.h"
#include "SDL2/SDL_render.h"
#include "Vector2D.hpp"
#include <iostream>
#include <ostream>

Map *map;

SDL_Renderer *Game::renderer;
SDL_Event *Game::event = new SDL_Event();

Manager manager;

std::vector<ColliderComponent *> Game::colliders;

Entity &player = manager.addEntity();
Entity &wall = manager.addEntity();

Entity &tile0 = manager.addEntity();
Entity &tile1 = manager.addEntity();
Entity &tile2 = manager.addEntity();

Game::Game() {}
Game::~Game() {}

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullScreen) {
    int flags = 0;
    if (fullScreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "Subsystems initialised!" << std::endl;
        this->window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

        if (this->window) {
            std::cout << "Window created!" << std::endl;
        }

        this->renderer = SDL_CreateRenderer(this->window, -1, 0);

        if (this->renderer) {
            SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);
            std::cout << "Renderer created!" << std::endl;
            this->isRunning = true;
        }
    }

    // bg1Texture = TextureManager::LoadTexture(this->renderer,
    // "assets/Battleground1/Pale/sky.png"); bg1DestR.x = -800;

    // bg2Texture =
    //     TextureManager::LoadTexture(this->renderer, "assets/Battleground1/Pale/ruins_bg.png");

    // bg3Texture =
    //     TextureManager::LoadTexture(this->renderer, "assets/Battleground1/Pale/hills&trees.png");

    // bg4Texture = TextureManager::LoadTexture(this->renderer,
    // "assets/Battleground1/Pale/ruins.png");

    // bg5Texture =
    //     TextureManager::LoadTexture(this->renderer, "assets/Battleground1/Pale/ruins2.png");

    // bg6Texture =
    //     TextureManager::LoadTexture(this->renderer,
    //     "assets/Battleground1/Pale/stones&grass.png");

    map = new Map();

    player.addComponent<TransformComponent>();
    player.addComponent<SpriteComponent>("assets/Knight_1/Walk.png");
    player.addComponent<KeyboardController>();
    player.addComponent<ColliderComponent>("player");

    tile0.addComponent<TileComponent>(300, 300, 32, 32, 0);

    tile1.addComponent<TileComponent>(350, 350, 32, 32, 1);
    tile1.addComponent<ColliderComponent>("dirt");

    tile2.addComponent<TileComponent>(250, 250, 32, 32, 2);
    tile2.addComponent<ColliderComponent>("grass");

    wall.addComponent<TransformComponent>(300.0f, 300.0f, 20, 200, 1);
    wall.addComponent<SpriteComponent>("assets/dirt.png");
    wall.addComponent<ColliderComponent>("wall");
}

void Game::handleEvents() {
    SDL_PollEvent(Game::event);

    switch (Game::event->type) {
    case SDL_QUIT:
        isRunning = false;
        break;

    default:
        break;
    }
}

void Game::update() {
    manager.refresh();
    manager.update();
    for (int i = 0; i < this->colliders.size(); i++) {
        if (Collision::AABB(player.getComponent<ColliderComponent>(), *this->colliders[i])) {
            // player.getComponent<TransformComponent>().velocity * -1;
        }
        // std::cout << "hit something" << std::endl;
    }

    if (player.getComponent<TransformComponent>().position.x > 100) {
        player.getComponent<SpriteComponent>().setStep(2);
    } else {
        player.getComponent<SpriteComponent>().setStep(1);
    }

    if (player.getComponent<TransformComponent>().position.x > 1000) {
        player.getComponent<TransformComponent>().position.x = 0;
    }
}

void Game::render() {
    SDL_RenderClear(this->renderer);
    // this is where you render stuff, images, sprites

    // map->draw();
    manager.draw();

    SDL_RenderPresent(this->renderer);
}

void Game::clean() {
    SDL_DestroyWindow(this->window);
    SDL_DestroyRenderer(this->renderer);
    SDL_Quit();
    std::cout << "Game Cleaned" << std::endl;
}

bool Game::running() { return this->isRunning; }
