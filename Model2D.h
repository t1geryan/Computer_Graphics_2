#pragma once
#include <vector>
#include "Vector2D.h"
#include "Matrix.h"
#include "Camera.h"
#include <Windows.h>

class Model2D
{
public:
	Model2D() = default;
	Model2D(const std::vector<Vector2D> &vertices, const std::vector<int> indices);

	void draw(const HDC& hdc, int left, int top, int right, int bottom);

private:
	std::vector<Vector2D> m_vertices;
	std::vector<int> m_indices;

	Matrix<> m_modelMatrix;
};
