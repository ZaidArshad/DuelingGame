#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Box.h"
#include "Shader/Color.h"
#include "Helper/AppTools.h"

#include <iostream>

Box::Box(float x, float y, float w, float h)
{
	// Generating position buffer
	m_width = w;
	m_height = h;
	m_x = x;
	m_y = y;
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
	delete m_pTexture;
}

void Box::setPosition(float x, float y)
{
	m_x = x;
	m_y = y;
	m_va.updateBuffer(0, getPosition());
}

void Box::setColor(float r, float g, float b, float a)
{
	std::vector<float> colors;
	for (int i = 0; i < 4; i++)
	{
		colors.insert(colors.end(), { r, g, b, a });
	}
	m_va.updateBuffer(1, colors);
}

void Box::setTexture(const std::string& path)
{
	std::vector<float> colors;
	for (int i = 0; i < 4; i++)
	{
		colors.insert(colors.end(), COLOR_TEXTURE.begin(), COLOR_TEXTURE.end());
	}
	m_va.updateBuffer(1, colors);
	m_pTexture = new Texture(path);
}

void Box::rotateModelX(float radians)
{
	m_modelMat =  glm::rotate(m_modelMat, radians, glm::vec3(0.0, 1.0, 0.0));
}


void Box::draw()
{
	if (m_pTexture)
	{
		m_pTexture->bind(0);
		m_va.draw();
		m_pTexture->unbind();
	}
	else
	{
		m_va.draw();
	}
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
