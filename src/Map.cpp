#include "Map.hpp"
#include "AssetManager.hpp"
#include "ECS/ColliderComponent.hpp"
#include "ECS/ECS.hpp"
#include "ECS/TileComponent.hpp"
#include "ECS/TransformComponent.hpp"
#include "Game.hpp"
#include "TextureManager.hpp"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

// this smells so bad... is there a proper way to access the manager?
extern Manager manager;

Map::Map(
    AssetId assetId,
    std::string coordinatesPath,
    int sizeX,
    int sizeY,
    int tileSize,
    int mapScale) {
    this->texture = Game::assets->get(assetId);
    this->coordinatesPath = coordinatesPath;
    this->sizeX = sizeX;
    this->sizeY = sizeY;
    this->tileSize = tileSize;
    this->mapScale = mapScale;
    this->scaledSize = tileSize * mapScale;
}

// passing size x and size y is stupid, the file should contain the size of the map. so dumb
// we could make the first two things be the size x and size y then the rest after a line break
// could be the map
void Map::render() {
    char tile;
    std::fstream mapFile;

    mapFile.open(coordinatesPath);

    int srcX;
    int srcY;

    // loads the textures pngs
    for (int y = 0; y < sizeY; y++) {
        for (int x = 0; x < sizeX; x++) {
            mapFile.get(tile);

            // atoi converts C-string (char) into a number
            // the way the tile map.map works is that the first number is the Y position in the
            // sprite terrain_ss.png. starting from 0 from bottom to the top.
            // then the second number is the X position in the sprite, starting also from 0, from
            // left to the right

            srcY = atoi(&tile) * this->tileSize;

            mapFile.get(tile);
            srcX = atoi(&tile) * this->tileSize;

            // std::cout << "Y(" << y << "), X(" << x << "): ";
            // std::cout << srcY << ", " << srcX << std::endl;

            // the tile is actualy 32px, but we're scaling it, so 64;
            addTile(srcX, srcY, x * scaledSize, y * scaledSize);

            // ignore comma
            mapFile.ignore();
        }
        // ignore line break
        mapFile.ignore();
    }

    // load the colliders
    // ignore empty line and line break
    mapFile.ignore();
    mapFile.ignore();

    // the second part of the file is where it indicates where the colliders will be
    // 1 indicates a collider, 0 indicates a place where you can navigate
    for (int y = 0; y < sizeY; y++) {
        for (int x = 0; x < sizeX; x++) {
            mapFile.get(tile);

            if (tile == '1') {
                Entity &tileCollider = manager.addEntity();
                tileCollider.addComponent<TransformComponent>(
                    x * scaledSize,
                    y * scaledSize,
                    scaledSize,
                    scaledSize);

                tileCollider.addComponent<ColliderComponent>("terrain");

                tileCollider.addGroup(GroupLabels::GROUP_COLLIDERS);
            }

            // ignore comma
            mapFile.ignore();
        }
        // ignore line break
        mapFile.ignore();
    }

    mapFile.close();
}

void Map::addTile(int srcX, int srcY, int posX, int posY) {
    Entity &tile = manager.addEntity();

    tile.addComponent<TileComponent>(texture, srcX, srcY, posX, posY, tileSize, mapScale);
    tile.addGroup(GroupLabels::GROUP_MAP);
}
