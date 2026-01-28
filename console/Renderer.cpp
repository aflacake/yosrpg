// console/Renderer.cpp

#include "Renderer.h"
#include <algorithm>

Renderer::Renderer(int width, int height)
    : screenWidth(width), screenHeight(height)
{
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    buffer.resize(screenWidth * screenHeight);
    clear();

    // pastikan cursor tidak kelihatan (biar bersih)
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.bVisible = FALSE;
    cursorInfo.dwSize = 1;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

Renderer::~Renderer() {
    // kosong — handle milik OS
}

void Renderer::clear() {
    std::fill(buffer.begin(), buffer.end(), L' ');
}

void Renderer::drawChar(int x, int y, wchar_t ch) {
    if (x < 0 || y < 0 || x >= screenWidth || y >= screenHeight)
        return;

    buffer[y * screenWidth + x] = ch;
}

void Renderer::drawSprite(
    int anchorX,
    int anchorY,
    const std::vector<std::wstring>& sprite
) {
    int spriteHeight = static_cast<int>(sprite.size());
    if (spriteHeight == 0) return;

    int spriteWidth = static_cast<int>(sprite[0].size());

    // anchor = kaki → baris terakhir
    int topLeftX = anchorX - spriteWidth / 2;
    int topLeftY = anchorY - spriteHeight + 1;

    for (int row = 0; row < spriteHeight; ++row) {
        for (int col = 0; col < spriteWidth; ++col) {
            wchar_t ch = sprite[row][col];

            // transparansi
            if (ch == L'░')
                continue;

            int screenX = topLeftX + col;
            int screenY = topLeftY + row;

            if (screenX < 0 || screenY < 0 ||
                screenX >= screenWidth || screenY >= screenHeight)
                continue;

            buffer[screenY * screenWidth + screenX] = ch;
        }
    }
}

void Renderer::present() {
    writeBufferToConsole();
}

void Renderer::writeBufferToConsole() {
    DWORD charsWritten = 0;
    COORD origin = { 0, 0 };

    WriteConsoleOutputCharacterW(
        hConsole,
        buffer.data(),
        static_cast<DWORD>(buffer.size()),
        origin,
        &charsWritten
    );
}

int Renderer::getWidth() const {
    return screenWidth;
}

int Renderer::getHeight() const {
    return screenHeight;
}
