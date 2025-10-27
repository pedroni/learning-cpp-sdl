#ifndef AssetManager_hpp
#define AssetManager_hpp

#include "ECS/ECS.hpp"
#include "SDL2/SDL_render.h"
#include "Vector2D.hpp"
#include <map>
#include <string>

using AssetId = std::string;

class AssetManager {
  public:
    AssetManager(Manager *manager);
    ~AssetManager();

    // game objects
    void
    createProjectile(AssetId assetId, Vector2D position, Vector2D velocity, int range, int speed);

    // texture management
    void add(AssetId id, const char *path);
    SDL_Texture *get(AssetId id);

  private:
    Manager *manager_;
    std::map<AssetId, SDL_Texture *> textures;
};

#endif
