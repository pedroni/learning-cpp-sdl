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
#include "SDL2/SDL_rect.h"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_timer.h"
#include "Vector2D.hpp"
#include <iostream>
#include <ostream>
#include <vector>

SDL_Renderer *Game::renderer;
SDL_Event *Game::event = new SDL_Event();
bool Game::isRunning = true;
SDL_Rect Game::camera = {0, 0, 800, 640};

Manager manager;

std::vector<ColliderComponent *> Game::colliders;

Entity &player = manager.addEntity();
// Entity &wall = manager.addEntity();

const char *mapFile = "assets/MapAssets/terrain_ss.png";

Game::Game() {}
Game::~Game() {}

std::vector<Entity *> &tiles = manager.getGroup(GroupLabels::GROUP_MAP);
std::vector<Entity *> &players = manager.getGroup(GroupLabels::GROUP_PLAYERS);
std::vector<Entity *> &enemies = manager.getGroup(GroupLabels::GROUP_ENEMIES);

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

    Map::load("assets/MapAssets/map.map", 25, 20);

    player.addComponent<TransformComponent>(64, 128);

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
    manager.refresh();
    manager.update();

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

    if ((SDL_GetTicks() % 50 == 0)) {
        std::cout << "Camera: x=" << camera.x << ", y=" << camera.y
                  << ", Player: x=" << player.getComponent<TransformComponent>().position.x
                  << ", y=" << player.getComponent<TransformComponent>().position.y << std::endl;
    }

    for (int i = 0; i < this->colliders.size(); i++) {
        if (Collision::AABB(player.getComponent<ColliderComponent>(), *this->colliders[i])) {
            // player.getComponent<TransformComponent>().velocity * -1;
        }
        // std::cout << "hit something" << std::endl;
    }
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

    SDL_RenderPresent(this->renderer);
}

void Game::clean() {
    SDL_DestroyWindow(this->window);
    SDL_DestroyRenderer(this->renderer);
    SDL_Quit();
    std::cout << "Game Cleaned" << std::endl;
}

bool Game::running() { return this->isRunning; }

void Game::addTile(int srcX, int srcY, int posX, int posY) {
    Entity &tile = manager.addEntity();

    tile.addComponent<TileComponent>(srcX, srcY, posX, posY, mapFile);
    tile.addGroup(GroupLabels::GROUP_MAP);
}
