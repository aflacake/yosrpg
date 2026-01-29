// core/Game.h

#pragma once

#include "../console/Renderer.h"
#include "../world/World.h"
#include "../entity/Player.h"
#include "Camera.h"

class Game {
public:
    Game();
    void run();

private:
    void update(float dt);
    void render(float time);

    Camera camera;
	Renderer renderer;
    World world;
    Player player;

    bool running;
};
	