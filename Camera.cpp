#include "Camera.h"

Camera::Camera(double x, double y): x(x), y(y) 
{}

Camera::Camera(Vector2D coordinates): x(coordinates.x()), y(coordinates.y()) 
{}

Vector2D Camera::toScreenCoordiantes(int width, int height)
{
    double deltaX = 10, deltaY = 5;
    double newX = (x + deltaX)*0.5*width, newY = (deltaY - y)*0.5*height;
    return Vector2D(newX, newY);
}
