#include "Map.hpp"
#include "Game.hpp"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <ostream>

// passing size x and size y is stupid, the file should contain the size of the map. so dumb
// we could make the first two things be the size x and size y then the rest after a line break
// could be the map
void Map::load(std::string path, int sizeX, int sizeY) {
    char tile;
    std::fstream mapFile;

    mapFile.open(path);

    int srcX;
    int srcY;

    for (int y = 0; y < sizeY; y++) {
        for (int x = 0; x < sizeX; x++) {
            mapFile.get(tile);

            // atoi converts C-string (char) into a number
            // the way the tile map.map works is that the first number is the Y position in the
            // sprite terrain_ss.png. starting from 0 from bottom to the top.
            // then the second number is the X position in the sprite, starting also from 0, from
            // left to the right

            srcY = atoi(&tile) * 32;

            mapFile.get(tile);
            srcX = atoi(&tile) * 32;

            // std::cout << "Y(" << y << "), X(" << x << "): ";
            // std::cout << srcY << ", " << srcX << std::endl;

            // the tile is actualy 32px, but we're scaling it, so 64;
            Game::addTile(srcX, srcY, x * 64, y * 64);

            mapFile.ignore();
        }
        mapFile.ignore();
    }

    mapFile.close();
}
