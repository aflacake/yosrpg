// world/Collision.h

#pragma once
#include "../entity/Entity.h"
#include "World.h"

class CollisionSystem {
public:
    static void update(Entity& e, World& world, float deltaTime);
};
