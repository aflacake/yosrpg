// assets/SpriteLoader.h

#pragma once

#include <vector>
#include <string>

class SpriteLoader {
public:
    // Load sprite ASCII dari file .txt (UTF-8, no BOM)
    static std::vector<std::wstring> load(const std::wstring& filePath);
};
