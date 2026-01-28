// core/Camera.cpp

#include "Camera.h"

Camera::Camera(int w, int h)
    : x(0), y(0), width(w), height(h)
{}

void Camera::follow(int targetX, int targetY) {
    x = targetX - width / 2;
    y = targetY - height / 2;
}
