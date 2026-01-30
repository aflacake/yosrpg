// world/TileAnimation.cpp

#include "TileAnimation.h"
#include <cmath>

wchar_t TileAnimation::getSymbol(
    TileType type,
    int x,
    int y,
    float time
) {
    // ===== WATER =====
    if (type == TileType::Water) {
        const wchar_t frames[] = { L'~', L'≈', L'∼' };
        int index = (x + y) % 3;
        return frames[index];
    }

    // ===== CLOUD =====
    if (type == TileType::Cloud) {
        return L'☁';
    }

    return L'?';
}
