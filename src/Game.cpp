#include "Game.hpp"
#include "Collision.hpp"
#include "ECS/Animation.hpp"
#include "ECS/ColliderComponent.hpp"
#include "ECS/ECS.hpp"
#include "ECS/KeyboardController.hpp"
#include "ECS/SpriteComponent.hpp"
#include "ECS/TransformComponent.hpp"
#include "Map.hpp"
#include "SDL2/SDL.h"
#include "SDL2/SDL_rect.h"
#include "SDL2/SDL_render.h"
#include "Vector2D.hpp"
#include <iostream>
#include <ostream>
#include <vector>

SDL_Renderer *Game::renderer;
SDL_Event *Game::event = new SDL_Event();
bool Game::isRunning = true;
SDL_Rect Game::camera = {0, 0, 800, 640};

Manager manager;

Entity &player = manager.addEntity();
// Entity &wall = manager.addEntity();

Game::Game() {}
Game::~Game() {}

std::vector<Entity *> &tiles = manager.getGroup(GroupLabels::GROUP_MAP);
std::vector<Entity *> &players = manager.getGroup(GroupLabels::GROUP_PLAYERS);
std::vector<Entity *> &enemies = manager.getGroup(GroupLabels::GROUP_ENEMIES);
std::vector<Entity *> &colliders = manager.getGroup(GroupLabels::GROUPS_COLLIDERS);

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

    Map map("assets/MapAssets/terrain_ss.png", "assets/MapAssets/map.map", 25, 20, 32, 2);
    map.render();

    // spawns the player at 540x430 coordinates
    player.addComponent<TransformComponent>(540, 430, 64, 128);

    std::vector<Animation> playerAnimations;
    playerAnimations.push_back(Animation("assets/Knight_1/Idle.png", 4, 128, 175));
    playerAnimations.push_back(Animation("assets/Knight_1/Walk.png", 8, 128, 200));
    playerAnimations.push_back(Animation("assets/Knight_1/Run.png", 7, 128, 125));
    player.addComponent<SpriteComponent>(playerAnimations);

    player.addComponent<KeyboardController>();
    player.addComponent<ColliderComponent>("player");
    player.addGroup(GroupLabels::GROUP_PLAYERS);

    // wall.addComponent<TransformComponent>(300.0f, 300.0f, 20, 200, 1);
    // wall.addComponent<SpriteComponent>("assets/dirt.png");
    // wall.addComponent<ColliderComponent>("wall");
    // wall.addGroup(GroupLabels::GROUP_MAP);
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
    SDL_Rect &playerCollider = player.getComponent<ColliderComponent>().collider;
    Vector2D previousPlayerPosition = player.getComponent<TransformComponent>().position;

    manager.refresh();
    manager.update();

    for (int i = 0; i < colliders.size(); i++) {
        SDL_Rect colliderRect = colliders[i]->getComponent<ColliderComponent>().collider;
        if (Collision::AABB(playerCollider, colliderRect)) {
            player.getComponent<TransformComponent>().position = previousPlayerPosition;
        }
    }

    // makes the camera follow the player, making it always at the center
    camera.x = player.getComponent<TransformComponent>().position.x - 340;
    camera.y = player.getComponent<TransformComponent>().position.y - 230;

    // bound camera to the window size
    if (camera.x < 0) {
        camera.x = 0;
    }

    if (camera.y < 0) {
        camera.y = 0;
    }

    // don't allow to grow bigger than the width of the camera
    if (camera.x > camera.w) {
        camera.x = camera.w;
    }

    // same, but for height
    if (camera.y > camera.h) {
        camera.y = camera.h;
    }

    // if ((SDL_GetTicks() % 50 == 0)) {
    //     std::cout << "Camera: x=" << camera.x << ", y=" << camera.y
    //               << ", Player: x=" << player.getComponent<TransformComponent>().position.x
    //               << ", y=" << player.getComponent<TransformComponent>().position.y << std::endl;
    // }
}

void Game::render() {
    SDL_RenderClear(this->renderer);

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

    for (int i = 0; i < colliders.size(); i++) {
        colliders[i]->draw();
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
