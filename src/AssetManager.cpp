#include "AssetManager.hpp"
#include "ECS/Animation.hpp"
#include "ECS/ColliderComponent.hpp"
#include "ECS/ProjectileComponent.hpp"
#include "ECS/SpriteComponent.hpp"
#include "ECS/TransformComponent.hpp"
#include "TextureManager.hpp"
#include "Vector2D.hpp"
#include <string>

AssetManager::AssetManager(Manager *manager) : manager_(manager) {}

AssetManager::~AssetManager() {}

// the fuck... we should probably have something else.. a projectile factory? ... this definitely is
// smelling. It doesn't belong here 🤣
void AssetManager::createProjectile(
    AssetId assetId,
    Vector2D position,
    Vector2D velocity,
    int range,
    int speed) {

    Entity &projectile = manager_->addEntity();
    projectile.addComponent<TransformComponent>(position.x, position.y, 35, 17, 1);
    projectile.addComponent<SpriteComponent>(Animation("fireball", 5, 35, 100));
    projectile.addComponent<ProjectileComponent>(range, speed, velocity);
    projectile.addComponent<ColliderComponent>("fireball", position.x, position.y, 35, 17);
    projectile.addGroup(GroupLabels::GROUP_PROJECTILES);
}

void AssetManager::add(AssetId id, const char *path) {
    textures.emplace(id, TextureManager::load(path));
}

SDL_Texture *AssetManager::get(AssetId id) { return textures.at(id); }
