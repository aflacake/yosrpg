// entity/Entity.h

#pragma once
#include <vector>
#include <string>

enum class Direction {
    Left,
    Right
};

enum class PhysicalState {
    Idle,
    Walk,
    Fall,
    HitWall,
    InWater
};

struct CollisionBox {
    int width;   // tile
    int height;  // tile
};

class Entity {
public:
    float posX, posY;      // posisi KAKI (world coordinate)
    float velX, velY;

    Direction direction;
    PhysicalState physicalState = PhysicalState::Idle;

    CollisionBox collider;

    bool facingRight = true;
    bool onGround;
    bool blocked;
    bool inWater;

    Entity();

    void setSprite(const std::vector<std::wstring>& s);
    const std::vector<std::wstring>& getSprite() const;

    int getX() const { return (int)posX; }
    int getY() const { return (int)posY; }

private:
    std::vector<std::wstring> sprite; // simpan langsung, bukan pointer
};
