#include "Map.hpp"
#include "Game.hpp"
#include <cstdlib>
#include <fstream>

// passing size x and size y is stupid, the file should contain the size of the map. so dumb
// we could make the first two things be the size x and size y then the rest after a line break
// could be the map
void Map::load(std::string path, int sizeX, int sizeY) {
    char tile;
    std::fstream mapFile;

    mapFile.open(path);

    for (int y = 0; y < sizeY; y++) {
        for (int x = 0; x < sizeX; x++) {
            mapFile.get(tile);
            Game::addTile(atoi(&tile), x * 32, y * 32);
            mapFile.ignore();
        }
    }

    mapFile.close();
}
