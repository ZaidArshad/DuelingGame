#include "Pyramid.h"
#include "Helper/AppTools.h"
#include "Shader/Color.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

Pyramid::Pyramid(float length)
{
	m_length = length;
	m_va.addBuffer(getPosition(), 3);

	std::vector<float> colors;
	for (int i = 0; i < 4; i++)
	{
		colors.insert(colors.end(), COLOR_WHITE.begin(), COLOR_WHITE.end());
	}
	m_va.addBuffer(colors, 4);

	//std::vector<float> textureCoords
	//{
	//	0.0f, 0.0f,
	//	1.0f, 0.0f,
	//	0.0f, 1.0f,
	//	1.0f, 1.0f
	//};
	//m_va.addBuffer(textureCoords, 2);

	// Generating index buffer
	std::vector<unsigned int> indices
	{
		0, 1, 2,
		0, 1, 3,
		0, 2, 3,
		1, 2, 3
	};
	m_va.setIndices(indices);
}

Pyramid::~Pyramid()
{
	delete m_pTexture;
}

void Pyramid::translate(float x, float y, float z)
{
	m_modelMat = glm::translate(m_modelMat, glm::vec3(x, y, z));
}

void Pyramid::rotateModelX(float radians)
{
	m_modelMat = glm::rotate(m_modelMat, radians, glm::vec3(0.5, 0.5, 0.0));
}

void Pyramid::draw()
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

std::vector<float> Pyramid::getPosition()
{

	std::vector<float> positions
	{
		-m_length,  m_length, m_length,
		m_length, m_length, m_length,
		0,  m_length, -m_length,
		0,  -m_length, 0
	};
	return positions;
}
