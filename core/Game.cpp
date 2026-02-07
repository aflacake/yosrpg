// core/Game.cpp

#include "Game.h"
#include "../world/TileAnimation.h"
#include "../world/Collision.h"
#include "../assets/SpriteLoader.h"

#include <chrono>
#include <thread>
#include <windows.h>

Game::Game()
    : camera(120, 40),
      renderer(120, 40),
      running(true)
{
    player.posX = 10;
    player.posY = 12;

    // ===== LOAD PLAYER SPRITES =====
    player.setIdleRight(
        SpriteLoader::load(
            L"..\\..\\assets\\sprites\\player\\idle_right.txt"
        )
    );

    player.setIdleLeft(
        SpriteLoader::load(
            L"..\\..\\assets/sprites/player/idle_left.txt"
        )
    );

    player.setWalkRight(
        SpriteLoader::load(
            L"..\\..\\assets/sprites/player/walk_right_1.txt"
        ),
        SpriteLoader::load(
            L"..\\..\\assets/sprites/player/walk_right_2.txt"
        )
    );

    player.setWalkLeft(
        SpriteLoader::load(
            L"..\\..\\assets/sprites/player/walk_left_1.txt"
        ),
        SpriteLoader::load(
            L"..\\..\\assets/sprites/player/walk_left_2.txt"
        )
    );

    player.setFallRight(
        SpriteLoader::load(
            L"..\\..\\assets/sprites/player/fall_right.txt"
        )
    );

    player.setHitWallRight(
        SpriteLoader::load(
            L"..\\..\\assets/sprites/player/hit_wall_right.txt"
        )
    );

    player.setInWaterRight(
        SpriteLoader::load(
            L"..\\..\\assets/sprites/player/in_water_right.txt"
        )
    );
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
    // RENDER TILE WORLD (ANIMATED)
    // ===============================
    for (int sy = 0; sy < camera.height; ++sy) {
        for (int sx = 0; sx < camera.width; ++sx) {

            int wx = camera.x + sx;
            int wy = camera.y + sy;

            Tile tile = world.getVisualTileAt(wx, wy, 0.0f);

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
    // RENDER PLAYER (SPRITE BESAR)
    // ===============================
    renderer.drawSprite(
        player.getX() - camera.x,
        player.getY() - camera.y,
        player.getSprite()
    );

    renderer.present();
}
