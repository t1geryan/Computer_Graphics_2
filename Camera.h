#pragma once
#include "Vector2D.h"

class Camera {
public:
    Camera(double x, double y);
    Camera(Vector2D coordinates);
    ~Camera() = default;

    Vector2D toScreenCoordiantes(int width, int height);
private:
    double x, y;
};