// world/Chunk.h

#pragma once
#include "Tile.h"
#include <vector>

constexpr int CHUNK_WIDTH  = 32;
constexpr int CHUNK_HEIGHT = 16;

class Chunk {
public:
    Chunk(int cx, int cy);

    Tile getTile(int x, int y) const;

private:
    int chunkX, chunkY;
    std::vector<Tile> tiles;

    void generate();
};
