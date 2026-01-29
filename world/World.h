// world/World.h

#pragma once
#include "Chunk.h"
#include <map>
#include <utility>

class World {
public:
    Tile getTileAt(int worldX, int worldY);
	Tile getVisualTileAt(int worldX, int worldY, float time);

private:
    std::map<std::pair<int,int>, Chunk> chunks;

    Chunk& getChunk(int cx, int cy);
};
