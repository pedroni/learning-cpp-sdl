#ifndef TileComponent_hpp
#define TileComponent_hpp

#include "Components.hpp"
#include "SDL2/SDL_rect.h"
#include "SDL2/SDL_render.h"

class TileComponent : public Component {
  public:
    SDL_Texture *texture;
    SDL_Rect srcRect, destRect;

    TileComponent() {}
    TileComponent(int srcX, int srcY, int posX, int posY, const char *path) {
        this->texture = TextureManager::LoadTexture(path);

        // src rect means the rectangle that we want to get from our source file.
        // the x and y here, referr to the position that they're in the png (sprite) file
        this->srcRect.x = srcX;
        this->srcRect.y = srcY;

        // in here we have 32 because we want to get a square of 32px in our png sprite.
        this->srcRect.w = this->srcRect.h = 32;

        // dest rect means the window screen, that's why we have posX and posY, its the position on
        // the screen that we want to draw the thing
        this->destRect.x = posX;
        this->destRect.y = posY;

        // here we have 64 pixel because we're scaling the src rect to double its size, so that its
        // rendered twice as big in the screen
        this->destRect.w = this->destRect.h = 64;
    }

    ~TileComponent() { SDL_DestroyTexture(this->texture); }
    void init() override {}

    void draw() override { TextureManager::draw(texture, srcRect, destRect, SDL_FLIP_NONE); }
};

#endif
