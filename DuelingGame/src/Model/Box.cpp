#include "Box.h"
#include "Helper/AppTools.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

Box::Box(float x, float y, float w, float h)
{
	m_width = w;
	m_height = h;
	m_x = x;
	m_y = y;
	m_va.addBuffer(getPosition(), 2);

	std::vector<float> colors
	{
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
	};
	m_va.addBuffer(colors, 4);

	std::vector<unsigned int> indices
	{
		0, 1, 2,
		1, 2, 3
	};
	m_va.setIndices(indices);
}

Box::~Box()
{
}

void Box::setPosition(float x, float y)
{
	m_x = x;
	m_y = y;
	m_va.updateBuffer(0, getPosition());
}

void Box::setColor(float r, float g, float b, float a)
{
	std::vector<float> colors
	{
		r, g, b, 1.0f,
		r, g, b, 1.0f,
		r, g, b, 1.0f,
		r, g, b, 1.0f
	};
	m_va.updateBuffer(1, colors);
}

void Box::draw()
{
	m_va.draw();
}

std::vector<float> Box::getPosition()
{
	float left = AppTools::normalizeX(m_x);
	float right = AppTools::normalizeX(m_x + m_width);
	float top = AppTools::normalizeY(m_y);
	float bottom = AppTools::normalizeY(m_y + m_height);
	std::vector<float> positions
	{
		left,  top,
		right, top,
		left,  bottom,
		right, bottom
	};
	return positions;
}
