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

	std::vector<float> textureCoords
	{
		0.0f, 0.0f,
		6.0f, 0.0f,
		0.0f, 6.00f,
		6.00f, 6.00f
	};
	m_va.addBuffer(textureCoords, 2);

	// Generating index buffer
	std::vector<unsigned int> indices
	{
		1, 2, 3,
		0, 1, 2,
		0, 1, 3,
		0, 2, 3
	};
	m_va.setIndices(indices);
}

Pyramid::~Pyramid()
{
	delete m_pTexture;
}

void Pyramid::setTexture(const std::string& path)
{
	std::vector<float> colors;
	for (int i = 0; i < 4; i++)
	{
		colors.insert(colors.end(), COLOR_TEXTURE.begin(), COLOR_TEXTURE.end());
	}
	m_va.updateBuffer(1, colors);
	m_pTexture = new Texture(path);
}

std::vector<float> Pyramid::getPosition()
{

	std::vector<float> positions
	{
		-m_length,  -m_length,  m_length, // left,   bottom, front
		 m_length,  -m_length,  m_length, // right,  botton, front
		 0,		    -m_length, -m_length, // center, bottom, back
		 0,			 m_length,  0		  // center, top,    middle
	};
	return positions;
}
