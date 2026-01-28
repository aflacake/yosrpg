// console/Renderer.h

#pragma once

#include <vector>
#include <string>
#include <windows.h>

class Renderer {
public:
    Renderer(int width, int height);
    ~Renderer();

    // frame control
    void clear();
    void present();

    // draw operations
    void drawChar(int x, int y, wchar_t ch);
    void drawSprite(
        int anchorX,
        int anchorY,
        const std::vector<std::wstring>& sprite
    );

    int getWidth() const;
    int getHeight() const;

private:
    int screenWidth;
    int screenHeight;

    HANDLE hConsole;
    std::vector<wchar_t> buffer;

    void writeBufferToConsole();
};
