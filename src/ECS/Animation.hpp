#ifndef Animation_hpp
#define Animation_hpp

#include "../AssetManager.hpp"
#include "../Game.hpp"
#include "SDL2/SDL_render.h"
#include <string>

struct Animation {
    SDL_Texture *texture;
    int frames;
    int frameWidth;
    int speed;

    Animation() {}

    Animation(AssetId assetId, int frames, int frameWidth, int speed) {
        this->texture = Game::assets->get(assetId);
        this->frames = frames;
        this->frameWidth = frameWidth;
        this->speed = speed;
    }
};

#endif
