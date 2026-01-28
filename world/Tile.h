// world/Tile.h

#pragma once
#include <wchar.h>

enum class TileType {
    Empty,
    Grass,
    Water,
    Dirt,
    Cliff,
    Cloud
};

struct TileVisual {
    wchar_t symbol;
};

struct Tile {
    TileType type;
    wchar_t symbol;
    bool solid;

    Tile(TileType t = TileType::Empty)
        : type(t), solid(false)
    {
        switch (type) {
        case TileType::Grass: symbol = L'.'; break;
        case TileType::Water: symbol = L'~'; break;
        case TileType::Dirt:  symbol = L':'; break;
        case TileType::Cliff: symbol = L'#'; solid = true; break;
        default: symbol = L' '; break;
        }
    }
};
