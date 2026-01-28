// entity/Player.h

#pragma once

#include "Entity.h"
#include <vector>
#include <string>

// state sederhana dulu
enum class PlayerState {
    Idle,
    Walk
};

class Player : public Entity {
public:
    Player();

    // update per frame
    void update(float deltaTime);

    // sprite setter (diisi dari luar / asset manager)
    void setIdleRight(const std::vector<std::wstring>& s);
    void setIdleLeft(const std::vector<std::wstring>& s);
    void setWalkRight(const std::vector<std::wstring>& s1,
                      const std::vector<std::wstring>& s2);
    void setWalkLeft(const std::vector<std::wstring>& s1,
                     const std::vector<std::wstring>& s2);

private:
    void handleInput();
    void updateSprite(float deltaTime);

    PlayerState state;

    // animasi
    float animTimer;
    int currentFrame; // 0 / 1

    // sprite bank
    std::vector<std::wstring> idleRight;
    std::vector<std::wstring> idleLeft;

    std::vector<std::wstring> walkRight[2];
    std::vector<std::wstring> walkLeft[2];

    int speed; // gerak horizontal (karakter per detik)
};
