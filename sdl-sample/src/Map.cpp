#include "Map.hpp"
#include "SDL2/SDL_render.h"
#include "TextureManager.hpp"

const int W = 0;
const int G = 1;
const int D = 2;

int lvl1[20][25] = {
    {
        0, 0, 0, 0, G, G, G, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    },
    {
        0, 0, 0, 0, 0, G, G, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    },
    {
        0, 0, 0, 0, 0, 0, G, G, G, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    },
    {
        0, 0, 0, 0, 0, 0, D, D, D, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    },
    {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    },
    {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    },
    {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    },
    {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    },
    {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    },
    {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    },
    {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    },
    {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    },
    {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    },
    {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    },
    {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    },
    {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    },
    {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    },
    {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    },
    {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    },
    {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    },
};

Map::Map() {
    this->dirt = TextureManager::LoadTexture("assets/dirt.png");
    this->grass = TextureManager::LoadTexture("assets/grass.png");
    this->water = TextureManager::LoadTexture("assets/water.png");

    this->load(lvl1);

    this->src.x = this->src.y = 0;

    this->src.w = 128;
    this->src.h = 128;

    this->dest.x = this->dest.y = 0;
    this->dest.w = 32;
    this->dest.h = 32;
}

Map::~Map() {
    SDL_DestroyTexture(grass);
    SDL_DestroyTexture(water);
    SDL_DestroyTexture(dirt);
}

void Map::load(int arr[20][25]) {
    for (int row = 0; row < 20; row++) {
        for (int col = 0; col < 25; col++) {
            this->map[row][col] = arr[row][col];
        }
    }
}

void Map::draw() {
    int type = W;

    for (int row = 0; row < 20; row++) {
        for (int col = 0; col < 25; col++) {
            type = this->map[row][col];
            this->dest.x = col * 32;
            this->dest.y = row * 32;

            switch (type) {
            case W:
                TextureManager::draw(this->water, this->src, this->dest);
                break;
            case G:
                TextureManager::draw(this->grass, this->src, this->dest);
                break;
            case D:
                TextureManager::draw(this->dirt, this->src, this->dest);
                break;
            }
        }
    }
}
