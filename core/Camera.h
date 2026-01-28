// core/Camera.h

#pragma once

class Camera {
public:
    int x, y;
    int width, height;

    Camera(int w, int h);

    void follow(int targetX, int targetY);
};
