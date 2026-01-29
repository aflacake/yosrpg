// entity/Player.cpp

#include "Player.h"
#include <windows.h>

Player::Player()
    : animTimer(0.0f),
      currentFrame(0),
      speed(20)
{
    direction = Direction::Right;
    facingRight = true;
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
    updateAnimation(deltaTime);
    applySprite();
}

void Player::handleInput() {
    bool left  = (GetAsyncKeyState('A') & 0x8000) ||
                 (GetAsyncKeyState(VK_LEFT) & 0x8000);

    bool right = (GetAsyncKeyState('D') & 0x8000) ||
                 (GetAsyncKeyState(VK_RIGHT) & 0x8000);

    if (left) {
        posX -= speed * 0.016f;
        facingRight = false;
    }
    else if (right) {
        posX += speed * 0.016f;
        facingRight = true;
    }

    // JANGAN set physicalState di sini
}

void Player::updateAnimation(float deltaTime) {
    if (physicalState == PhysicalState::Walk) {
        animTimer += deltaTime;
        if (animTimer >= 0.15f) {
            animTimer = 0.0f;
            currentFrame = (currentFrame + 1) % 2;
        }
    } else {
        currentFrame = 0;
        animTimer = 0.0f;
    }
}

void Player::applySprite() {
    if (facingRight) {
        switch (physicalState) {
        case PhysicalState::Idle:
            setSprite(idleRight);
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
    } else {
        switch (physicalState) {
        case PhysicalState::Idle:
            setSprite(idleLeft);
            break;
        case PhysicalState::Walk:
            setSprite(walkLeft[currentFrame]);
            break;
        default:
            setSprite(idleLeft); // fallback aman
            break;
        }
    }
}
