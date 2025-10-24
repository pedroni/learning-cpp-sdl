#include "Game.hpp"
#include "Collision.hpp"
#include "ECS/Animation.hpp"
#include "ECS/ColliderComponent.hpp"
#include "ECS/ECS.hpp"
#include "ECS/KeyboardController.hpp"
#include "ECS/SpriteComponent.hpp"
#include "ECS/TileComponent.hpp"
#include "ECS/TransformComponent.hpp"
#include "Map.hpp"
#include "SDL2/SDL.h"
#include "SDL2/SDL_render.h"
#include "Vector2D.hpp"
#include <array>
#include <iostream>
#include <ostream>
#include <vector>

SDL_Renderer *Game::renderer;
SDL_Event *Game::event = new SDL_Event();

Manager manager;

std::vector<ColliderComponent *> Game::colliders;

Entity &player = manager.addEntity();
Entity &wall = manager.addEntity();

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

    Map::load("assets/p16x16.map", 16, 16);

    player.addComponent<TransformComponent>(64, 128);

    std::vector<Animation> playerAnimations;
    playerAnimations.push_back(Animation("assets/Knight_1/Idle.png", 4, 175, 128));
    playerAnimations.push_back(Animation("assets/Knight_1/Walk.png", 8, 200, 128));
    playerAnimations.push_back(Animation("assets/Knight_1/Run.png", 7, 175, 128));
    player.addComponent<SpriteComponent>(playerAnimations);

    player.addComponent<KeyboardController>();
    player.addComponent<ColliderComponent>("player");
    player.addGroup(GroupLabels::GROUP_PLAYERS);

    wall.addComponent<TransformComponent>(300.0f, 300.0f, 20, 200, 1);
    wall.addComponent<SpriteComponent>("assets/dirt.png");
    wall.addComponent<ColliderComponent>("wall");
    wall.addGroup(GroupLabels::GROUP_MAP);
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

    if (player.getComponent<TransformComponent>().position.x > 1000) {
        player.getComponent<TransformComponent>().position.x = 0;
    }
}

void Game::render() {
    SDL_RenderClear(this->renderer);

    std::vector<Entity *> &tiles = manager.getGroup(GroupLabels::GROUP_MAP);
    std::vector<Entity *> &players = manager.getGroup(GroupLabels::GROUP_PLAYERS);
    std::vector<Entity *> &enemies = manager.getGroup(GroupLabels::GROUP_ENEMIES);

    // this is where you render stuff, images, sprites

    // map->draw();
    // before we'd render everything out of the manager draw, now we use the groups to render in the
    // order that we want instead of order of declaration
    //
    // 💡i think this is how we handle z index too. i guess we'd have to sort the vector based of z
    // index and then place them at the correct order!!! thats awesome, i think im finally getting
    // some ideas on how to implement things on my own.
    //
    // c++ is fast so they say, so that shouldnt be a problem to sort on an infinite while loop
    //
    //
    // manager.draw();

    for (int i = 0; i < tiles.size(); i++) {
        tiles[i]->draw();
    }

    for (int i = 0; i < players.size(); i++) {
        players[i]->draw();
    }

    for (int i = 0; i < enemies.size(); i++) {
        enemies[i]->draw();
    }

    SDL_RenderPresent(this->renderer);
}

void Game::clean() {
    SDL_DestroyWindow(this->window);
    SDL_DestroyRenderer(this->renderer);
    SDL_Quit();
    std::cout << "Game Cleaned" << std::endl;
}

bool Game::running() { return this->isRunning; }

void Game::addTile(int id, int x, int y) {
    Entity &tile = manager.addEntity();

    tile.addComponent<TileComponent>(x, y, 32, 32, id);
    tile.addGroup(GroupLabels::GROUP_MAP);
}
