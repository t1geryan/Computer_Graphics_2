#pragma once
#include <vector>
#include "Camera.h"
#include "Loader.h"
#include <Windows.h>
#include <windef.h>
#include <wingdi.h>
#include "Matrix.h"
#include <windowsx.h>
#include "AffineTransform.h"

class Model2D
{
public:
	Model2D() = default;
	Model2D(const std::vector<Vector2D> &vertices, const std::vector<int> indices);
	Model2D(const Loader loader);

	Vector2D getVertex(const int index);
	void draw(const HDC& hdc, int left, int top, int right, int bottom);

	void translate(double x, double y);
	void rotate(double angle);
	void scale(double x, double y);
	void reflect(bool isOnX, bool isOnY);

	void setBorderColor(int color);
private:
	Matrix<double> m_vertices;
	std::vector<int> m_indices;

	int borderColor = 0x000000;

	void applyTransform(Matrix<double> transformMatrix);
};
