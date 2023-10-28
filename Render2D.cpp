#include "Render2D.h"

Render2D::~Render2D()
{
	for (const auto& object : m_objects)
		if (object)
			delete object;
}

void Render2D::draw(const HDC& hdc)
{
	int left = 10, top = 10, right = 210, bottom = 210;
	int margin = 50;
	for (const auto& object : m_objects)
		if (object) {
			object->draw(hdc, left, top, right, bottom);
			left += margin;
			right += margin;
		}
}

void Render2D::addObject(Model2D* model)
{
	m_objects.push_back(model);
}
