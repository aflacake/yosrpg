// world/TileAnimation.h

#pragma once
#include "Tile.h"

class TileAnimation {
public:
    static wchar_t getSymbol(
        TileType type,
        int worldX,
        int worldY,
        float time
    );
};
