// entity/Entity.cpp

#include "Entity.h"

Entity::Entity()
    : posX(0), posY(0),
      velX(0), velY(0),
      direction(Direction::Right),
      physicalState(PhysicalState::Idle),
      collider{1, 2},
      facingRight(true),
      onGround(false),
      blocked(false),
      inWater(false),
      sprite(nullptr)
{}

void Entity::setSprite(const std::vector<std::wstring>& s) {
    sprite = &s;
}

const std::vector<std::wstring>& Entity::getSprite() const {
    static std::vector<std::wstring> empty;
    if (!sprite) return empty;
    return *sprite;
}
