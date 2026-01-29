// core/Game.cpp

#include "Game.h"
#include "../world/TileAnimation.h"
#include "../world/Collision.h"
#include <chrono>
#include <thread>

Game::Game()
    : camera(120, 40), 
      renderer(120, 40), 
      running(true)
{
    // posisi awal player (kaki)
    player.posX = 10;
    player.posY = 12;

    // === FIX #5B: sprite awal player ===
    player.setIdleRight({
        L" O ",
        L"/|\\",
        L"/ \\"
    });
}

void Game::run() {

    using clock = std::chrono::high_resolution_clock;
    auto last = clock::now();
    float time = 0.0f;

    while (running) {
        auto now = clock::now();
        std::chrono::duration<float> dt = now - last;
        last = now;

        time += dt.count();

        update(dt.count());
        render(time);

        std::this_thread::sleep_for(
            std::chrono::milliseconds(16)
        );
    }
}

void Game::update(float dt) {

    // input global (opsional, boleh dihapus nanti)
    player.velX = 0;

    if (GetAsyncKeyState('A') & 0x8000)
        player.velX = -12;
    if (GetAsyncKeyState('D') & 0x8000)
        player.velX = 12;

    // physics & collision
    CollisionSystem::update(player, world, dt);

    // ⬇️ BIARKAN PLAYER MENGURUS DIRINYA SENDIRI
    player.update(dt);

    // kamera
    camera.follow(player.getX(), player.getY());
}

void Game::render(float time) {

    renderer.clear();

    // ===============================
    // 1️⃣ RENDER TILE WORLD (ANIMATED)
    // ===============================
    for (int sy = 0; sy < camera.height; ++sy) {
        for (int sx = 0; sx < camera.width; ++sx) {

            int wx = camera.x + sx;
            int wy = camera.y + sy;

            Tile tile =
                world.getVisualTileAt(wx, wy, time);

            if (tile.type == TileType::Water) {
                wchar_t w =
                    TileAnimation::getSymbol(
                        tile.type, wx, wy, time
                    );
                renderer.drawChar(sx, sy, w);
            }
            else {
                renderer.drawChar(sx, sy, tile.symbol);
            }
        }
    }

    // ===============================
    // 2️⃣ RENDER PLAYER (SPRITE BESAR)
    // ===============================
    renderer.drawSprite(
        player.getX() - camera.x,
        player.getY() - camera.y - 16,
        player.getSprite()
    );

    renderer.present();
}
