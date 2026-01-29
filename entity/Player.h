// entity/Player.h

#pragma once

#include "Entity.h"
#include <vector>
#include <string>

class Player : public Entity {
public:
    Player();
    void update(float deltaTime);

    // setter sprite
    void setIdleRight(const std::vector<std::wstring>& s);
    void setIdleLeft(const std::vector<std::wstring>& s);

    void setWalkRight(const std::vector<std::wstring>& s1,
                      const std::vector<std::wstring>& s2);
    void setWalkLeft(const std::vector<std::wstring>& s1,
                     const std::vector<std::wstring>& s2);

    void setFallRight(const std::vector<std::wstring>& s);
    void setFallLeft(const std::vector<std::wstring>& s);

    void setHitWallRight(const std::vector<std::wstring>& s);
    void setHitWallLeft(const std::vector<std::wstring>& s);

    void setInWaterRight(const std::vector<std::wstring>& s);
    void setInWaterLeft(const std::vector<std::wstring>& s);

private:
    void handleInput();
    void updateAnimation(float deltaTime);
    void applySprite(); // ← SATU KALI SAJA

    float animTimer = 0.0f;
    int currentFrame = 0;
    int speed = 10;

    // sprite bank
    std::vector<std::wstring> idleRight;
    std::vector<std::wstring> idleLeft;

    std::vector<std::wstring> walkRight[2];
    std::vector<std::wstring> walkLeft[2];

    std::vector<std::wstring> fallRight;
    std::vector<std::wstring> fallLeft;

    std::vector<std::wstring> hitWallRight;
    std::vector<std::wstring> hitWallLeft;

    std::vector<std::wstring> inWaterRight;
    std::vector<std::wstring> inWaterLeft;
};
