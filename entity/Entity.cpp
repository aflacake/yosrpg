// entity/Entity.cpp

#include "Entity.h"

Entity::Entity()
    : posX(0), posY(0),
      velX(0), velY(0),
      direction(Direction::Right),
      state(PhysicalState::Idle),
      onGround(false),
      blocked(false),
      inWater(false),
      sprite(nullptr)
{
    collider.width  = 1;
    collider.height = 2;
}

void Entity::setSprite(const std::vector<std::wstring>& s) {
    sprite = &s;
}

const std::vector<std::wstring>& Entity::getSprite() const {
    return *sprite;
}
