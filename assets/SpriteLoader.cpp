// assets/SpriteLoader.cpp

#include "SpriteLoader.h"
#include <fstream>
#include <stdexcept>
#include <windows.h>

std::vector<std::wstring> SpriteLoader::load(const std::wstring& filePath) {
    std::vector<std::wstring> sprite;

    std::wifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open sprite file");
    }

    // Paksa mode UTF-8 → UTF-16 (Windows native)
    file.imbue(std::locale(
        std::locale(),
        new std::codecvt_utf8<wchar_t>
    ));

    std::wstring line;
    while (std::getline(file, line)) {
        // Hapus CR kalau file pakai Windows line ending
        if (!line.empty() && line.back() == L'\r') {
            line.pop_back();
        }

        sprite.push_back(line);
    }

    file.close();

    return sprite;
}
