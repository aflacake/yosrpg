// world/Collision.cpp

#include "Collision.h"
#include <cmath>

constexpr float GRAVITY = 35.0f;
constexpr float WATER_GRAVITY = 8.0f;
constexpr float MAX_FALL_SPEED = 40.0f;

void CollisionSystem::update(Entity& e, World& world, float dt) {

    // =========================
    // 1. GRAVITY
    // =========================
    float gravity = e.inWater ? WATER_GRAVITY : GRAVITY;
    e.velY += gravity * dt;

    if (e.velY > MAX_FALL_SPEED)
        e.velY = MAX_FALL_SPEED;

    // =========================
    // 2. VERTICAL MOVE
    // =========================
    float nextY = e.posY + e.velY * dt;

    Tile below = world.getTileAt(
        (int)e.posX,
        (int)std::floor(nextY) + 1
    );

    if (below.solid) {
        e.posY = std::floor(nextY);
        e.velY = 0;
        e.onGround = true;
    } else {
        e.posY = nextY;
        e.onGround = false;
    }

    // =========================
    // 3. WATER CHECK
    // =========================
    Tile current = world.getTileAt(
        (int)e.posX,
        (int)e.posY
    );

    e.inWater = current.liquid;

    // =========================
    // 4. HORIZONTAL MOVE
    // =========================
    e.blocked = false;

    if (e.velX != 0) {
        int dir = (e.velX > 0) ? 1 : -1;

        Tile frontFoot = world.getTileAt(
            (int)(e.posX + dir),
            (int)e.posY
        );

        Tile frontBody = world.getTileAt(
            (int)(e.posX + dir),
            (int)e.posY - 1
        );

        if (frontFoot.solid || frontBody.solid) {
            e.velX = 0;
            e.blocked = true;
        } else {
            e.posX += e.velX * dt;
        }
    }

    // =========================
    // 5. STATE MACHINE (FINAL)
    // =========================
    if (e.inWater) {
        e.state = PhysicalState::InWater;
    }
    else if (!e.onGround) {
        e.state = PhysicalState::Fall;
    }
    else if (e.blocked) {
        e.state = PhysicalState::HitWall;
    }
    else if (std::abs(e.velX) > 0.1f) {
        e.state = PhysicalState::Walk;
    }
    else {
        e.state = PhysicalState::Idle;
    }
}
