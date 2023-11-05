#include "Model2D.h"

Model2D::Model2D(const std::vector<Vector2D>& vertices, const std::vector<int> indices) :
	m_indices(indices),
	m_vertices(Matrix<double>(3, vertices.size()))
{
	for (size_t i = 0; i < vertices.size(); ++i) {
		m_vertices.setValue(0, i, vertices[i].x());
		m_vertices.setValue(1, i, vertices[i].y());
		m_vertices.setValue(2, i, 1);
	}
}

Model2D::Model2D(const Loader loader): Model2D(loader.vertices(), loader.indices()) {}

Vector2D Model2D::getVertex(const int index)
{
	return Vector2D(m_vertices.getValue(0, index), m_vertices.getValue(1, index));
}

void Model2D::draw(const HDC& hdc, int left, int top, int right, int bottom)
{
	HPEN pen = CreatePen(PS_SOLID, 1, borderColor);
	SelectObject(hdc, pen);
	if (m_vertices.nColumns() > 0) {
		int width = right - left, height = bottom - top;
		Vector2D currentVertex = Camera(getVertex(0)).toScreenCoordiantes(width, height);
		MoveToEx(hdc, left + (int) currentVertex.x(), top + (int) currentVertex.y(), NULL);
		for (size_t i = 1; i < m_indices.size(); ++i) {
			currentVertex = Camera(getVertex(m_indices[i])).toScreenCoordiantes(width, height);
			LineTo(hdc, left + (int) currentVertex.x(), top + (int) currentVertex.y());
		}
	}
	DeleteObject(pen);
}

void Model2D::translate(double x, double y)
{
	Matrix<double> transform = AffineTransform::Translation(x, y);
	applyTransform(transform);
}

void Model2D::rotate(double angle)
{
	Matrix<double> transform = AffineTransform::Rotation(angle);
	applyTransform(transform);
}

void Model2D::scale(double x, double y)
{
	Matrix<double> transform = AffineTransform::Scaling(x, y);
	applyTransform(transform);
}

void Model2D::reflect(bool isOnX, bool isOnY)
{
	if (!(isOnX || isOnY)) return;

	if (isOnX && isOnY)
		applyTransform(AffineTransform::ReflectAll());
	else if (isOnX)
		applyTransform(AffineTransform::ReflectOX());
	else
		applyTransform(AffineTransform::ReflectOY());
}

void Model2D::setBorderColor(int color)
{
	borderColor = color;
}

void Model2D::applyTransform(Matrix<double> transformMatrix)
{
	for (size_t j = 0; j < m_vertices.nColumns(); ++j) {
		Matrix<double> coordColumn = transformMatrix * m_vertices.getColumn(j);
		m_vertices.setColumn(j, coordColumn);
	}
}
