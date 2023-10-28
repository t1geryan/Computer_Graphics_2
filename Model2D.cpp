#include "Model2D.h"
#include <windef.h>
#include <wingdi.h>
#include <windowsx.h>

Model2D::Model2D(const std::vector<Vector2D>& vertices, const std::vector<int> indices) :
	m_vertices(vertices),
	m_indices(indices)
{
}

void Model2D::draw(const HDC& hdc, int left, int top, int right, int bottom)
{
	if (m_vertices.size() > 0) {
		int width = right - left, height = bottom - top;
		Vector2D currentVertex = Camera(m_vertices[0]).toScreenCoordiantes(width, height);
		MoveToEx(hdc, left + (int) currentVertex.x(), top + (int) currentVertex.y(), NULL);
		for (size_t i = 1; i < m_indices.size(); ++i) {
			currentVertex = Camera(m_vertices[m_indices[i]]).toScreenCoordiantes(width, height);
			LineTo(hdc, left + (int) currentVertex.x(), top + (int) currentVertex.y());
		}
	}
}
