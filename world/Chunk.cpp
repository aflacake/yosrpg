// world/Chunk.cpp

#include "Chunk.h"

Chunk::Chunk()
    : chunkX(0), chunkY(0)
{
    tiles.resize(CHUNK_WIDTH * CHUNK_HEIGHT);
    generate();
}

void Chunk::generate() {
    for (int y = 0; y < CHUNK_HEIGHT; ++y) {
        for (int x = 0; x < CHUNK_WIDTH; ++x) {

            if (y > 10)
                tiles[y * CHUNK_WIDTH + x] = Tile(TileType::Grass);
            else if (y == 10)
                tiles[y * CHUNK_WIDTH + x] = Tile(TileType::Dirt);
            else
                tiles[y * CHUNK_WIDTH + x] = Tile(TileType::Water);
        }
    }
}

Tile Chunk::getTile(int x, int y) const {
    return tiles[y * CHUNK_WIDTH + x];
}
