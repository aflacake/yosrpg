// assets/SpriteLoader.cpp

#include "SpriteLoader.h"
#include <fstream>
#include <stdexcept>
#include <windows.h>

std::vector<std::wstring> SpriteLoader::load(const std::wstring& filePath) {
    std::vector<std::wstring> sprite;

    // 🔹 Konversi wstring → string (UTF-8 path)
    std::string path(filePath.begin(), filePath.end());

    std::ifstream file(path);
    if (!file.is_open()) {
        MessageBoxA(
            NULL,
            path.c_str(),
            "SPRITE FILE NOT FOUND",
            MB_OK | MB_ICONERROR
        );
        throw std::runtime_error("Failed to open sprite file");
    }

    std::string line;
    while (std::getline(file, line)) {
        // hapus CR (Windows line ending)
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }

        // konversi ke wstring (ASCII aman)
        sprite.emplace_back(line.begin(), line.end());
    }

    return sprite;
}
