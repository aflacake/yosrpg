// entity/Player.cpp

#include "Player.h"
#include <windows.h>

Player::Player()
    : state(PlayerState::Idle),
      animTimer(0.0f),
      currentFrame(0),
      speed(20)
{
    direction = Direction::Right;
}

void Player::setIdleRight(const std::vector<std::wstring>& s) {
    idleRight = s;
}

void Player::setIdleLeft(const std::vector<std::wstring>& s) {
    idleLeft = s;
}

void Player::setWalkRight(const std::vector<std::wstring>& s1,
                          const std::vector<std::wstring>& s2) {
    walkRight[0] = s1;
    walkRight[1] = s2;
}

void Player::setWalkLeft(const std::vector<std::wstring>& s1,
                         const std::vector<std::wstring>& s2) {
    walkLeft[0] = s1;
    walkLeft[1] = s2;
}

void Player::update(float deltaTime) {
    handleInput();
    updateSprite(deltaTime);
}

void Player::handleInput() {
    bool left  = (GetAsyncKeyState('A') & 0x8000) ||
                 (GetAsyncKeyState(VK_LEFT) & 0x8000);

    bool right = (GetAsyncKeyState('D') & 0x8000) ||
                 (GetAsyncKeyState(VK_RIGHT) & 0x8000);

    if (left) {
        direction = Direction::Left;
        state = PlayerState::Walk;
        posX -= speed * 0.016f; // langkah kasar per frame
    }
    else if (right) {
        direction = Direction::Right;
        state = PlayerState::Walk;
        posX += speed * 0.016f;
    }
    else {
        state = PlayerState::Idle;
    }
}

void Player::updateSprite(float deltaTime) {
    animTimer += deltaTime;

    if (state == PlayerState::Walk) {
        if (animTimer >= 0.15f) {
            animTimer = 0.0f;
            currentFrame = (currentFrame + 1) % 2;
        }

        if (direction == Direction::Right) {
            setSprite(walkRight[currentFrame]);
        } else {
            setSprite(walkLeft[currentFrame]);
        }
    }
    else { // Idle
        currentFrame = 0;
        animTimer = 0.0f;

        if (direction == Direction::Right) {
            setSprite(idleRight);
        } else {
            setSprite(idleLeft);
        }
    }
}

void Player::applySprite() {
    if (direction == Direction::Right) {
        switch (state) {
        case PhysicalState::Idle:
            setSprite(idleGroundRight);
            break;
        case PhysicalState::Walk:
            setSprite(walkRight[currentFrame]);
            break;
        case PhysicalState::Fall:
            setSprite(fallRight);
            break;
        case PhysicalState::HitWall:
            setSprite(hitWallRight);
            break;
        case PhysicalState::InWater:
            setSprite(inWaterRight);
            break;
        }
    }
    // LEFT → manual asset, nanti
}
