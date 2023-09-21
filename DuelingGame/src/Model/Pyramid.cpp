#include "Pyramid.h"
#include "Helper/AppTools.h"
#include "Shader/Color.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

Pyramid::Pyramid(float x, float y, float z, float length)
{
	m_x = x;
	m_y = y;
	m_z = z;
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

void Pyramid::rotateModelX(float radians)
{
	m_modelMat = glm::rotate(m_modelMat, radians, glm::vec3(0.0, 0.5, 0.0));
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
	float left = AppTools::normalizeX(m_x);
	float right = AppTools::normalizeX(m_x + m_length);
	float midX = (left + right) / 2;

	float top = AppTools::normalizeY(m_y);
	float bot = AppTools::normalizeY(m_y+m_length);

	float front = AppTools::normalizeX(m_z);
	float back = AppTools::normalizeX(m_z + m_length);
	float midZ = (front + back) / 2;


	std::vector<float> positions
	{
		left,  bot, front,
		right, bot, front,
		midX,  bot, back,
		midX,  top, midZ
	};
	return positions;
}
