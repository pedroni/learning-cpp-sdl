#ifndef TileComponent_hpp
#define TileComponent_hpp

#include "../Game.hpp"
#include "../TextureManager.hpp"
#include "SDL2/SDL_rect.h"
#include "SDL2/SDL_render.h"
#include "TransformComponent.hpp"

class TileComponent : public Component {
  public:
    SDL_Texture *texture;

    // srcRect is where the tile texture is located at the png file
    SDL_Rect srcRect;

    // destRect is where the tile is drawn on the renderer
    SDL_Rect destRect;

    // position here is used to know where they're actually are ON in the WORLD, and not where
    // they're being drawn. we have the destRect which is the rectangle that represents where in the
    // rendered it's being drawn
    Vector2D worldPosition;

    TileComponent(
        SDL_Texture *texture,
        int srcX,
        int srcY,
        int posX,
        int posY,
        int tileSize,
        int tileScale) {
        this->texture = texture;

        this->worldPosition.x = posX;
        this->worldPosition.y = posY;

        // src rect means the rectangle that we want to get from our source file.
        // the x and y here, referr to the position that they're in the png (sprite) file
        this->srcRect.x = srcX;
        this->srcRect.y = srcY;

        // in here we have 32 because we want to get a square of 32px in our png sprite.
        this->srcRect.w = this->srcRect.h = tileSize;

        // dest rect means the window screen, that's why we have posX and posY, its the position on
        // the screen that we want to draw the thing
        this->destRect.x = posX;
        this->destRect.y = posY;

        // here we have 64 pixel because we're scaling the src rect to double its size, so that its
        // rendered twice as big in the screen
        this->destRect.w = this->destRect.h = tileSize * tileScale;
    }

    void init() override {}

    void update() override {
        // tile position is fixed! it never changes, however we change it on the screen by
        // calculating from the camera. the camera x and y changes as the player moves.
        // the position is like where it's in the world, the destRect is where it should be on the
        // screen
        destRect.x = worldPosition.x - Game::camera.x;
        destRect.y = worldPosition.y - Game::camera.y;
    }

    void draw() override { TextureManager::draw(texture, srcRect, destRect, SDL_FLIP_NONE); }
};

#endif
