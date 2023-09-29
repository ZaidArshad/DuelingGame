#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Box.h"
#include "Shader/Color.h"
#include "Helper/AppTools.h"

#include <iostream>

Box::Box(float w, float h)
{
	m_vertCount = 4;

	// Generating position buffer
	m_width = w;
	m_height = h;
	m_va.addBuffer(getPosition(), 2);

	// Generating color buffer to white
	std::vector<float> colors;
	for (int i = 0; i < 4; i++)
	{
		colors.insert(colors.end(), COLOR_WHITE.begin(), COLOR_WHITE.end());
	}
	m_va.addBuffer(colors, 4);

	std::vector<float> textureCoords
	{
		0.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f
	};
	m_va.addBuffer(textureCoords, 2);

	// Generating index buffer
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

// -- Overload -- //
std::vector<float> Box::getPosition()
{
	float left = -m_width/2;
	float right = m_width/2;
	float top = m_height/2;
	float bottom = -m_height/2;
	std::vector<float> positions
	{
		left,  top,
		right, top,
		left,  bottom,
		right, bottom
	};
	return positions;
}
