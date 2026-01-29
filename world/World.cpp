// world/World.cpp

#include "World.h"

Chunk& World::getChunk(int cx, int cy) {
    auto key = std::make_pair(cx, cy);

    if (chunks.find(key) == chunks.end()) {
        chunks.emplace(key, Chunk(cx, cy));
    }
    return chunks.at(key);
}

Tile World::getTileAt(int worldX, int worldY) {
    int cx = worldX / CHUNK_WIDTH;
    int cy = worldY / CHUNK_HEIGHT;

    int localX = worldX % CHUNK_WIDTH;
    int localY = worldY % CHUNK_HEIGHT;

    if (localX < 0) localX += CHUNK_WIDTH;
    if (localY < 0) localY += CHUNK_HEIGHT;

    return getChunk(cx, cy).getTile(localX, localY);
}

Tile World::getVisualTileAt(
    int worldX,
    int worldY,
    float time
) {
    // layer awan di langit
    if (worldY < 3) {
        int cloudX = worldX + (int)(time * 2);
        if ((cloudX % 16) < 6) {
            Tile cloud(TileType::Cloud);
            cloud.symbol = L'☁';
            return cloud;
        }
    }

    return getTileAt(worldX, worldY);
}
