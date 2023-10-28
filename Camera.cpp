#include "Camera.h"

Camera::Camera(double x, double y): x(x), y(y) 
{}

Camera::Camera(Vector2D coordinates): x(coordinates.x()), y(coordinates.y()) 
{}

Vector2D Camera::toScreenCoordiantes(int width, int height)
{
    double delta = 8;
    double newX = (x + delta)*0.5*width, newY = (delta - y)*0.5*height;
    return Vector2D(newX, newY);
}
