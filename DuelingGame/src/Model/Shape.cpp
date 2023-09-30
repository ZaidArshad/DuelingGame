#include "Shape.h"
#include "Shader/Color.h"
#include "glm/gtc/matrix_transform.hpp"

Shape::Shape()
{
	m_vertCount = 0;
	m_pTexture = nullptr;
	m_modelMat = glm::mat4(1.0f);
}

Shape::~Shape()
{
	delete m_pTexture;
}

// -- Setters -- //
void Shape::setColor(float r, float g, float b, float a)
{
	std::vector<float> colors;
	for (int i = 0; i < m_vertCount; i++)
	{
		colors.insert(colors.end(), { r, g, b, a });
	}
	m_va.updateBuffer(1, colors);
}

void Shape::setTexture(const std::string& path)
{
	std::vector<float> colors;
	for (int i = 0; i < m_vertCount; i++)
	{
		colors.insert(colors.end(), COLOR_TEXTURE.begin(), COLOR_TEXTURE.end());
	}
	m_va.updateBuffer(1, colors);
	m_pTexture = new Texture(path);
}

// -- Getters -- //
glm::mat4 Shape::getModelMatrix()
{
	return m_modelMat;
}

//  -- Utility -- //
void Shape::translate(float x, float y, float z)
{
	m_modelMat = glm::translate(m_modelMat, glm::vec3(x, y, z));
}

void Shape::rotateModel(float radians, float x, float y, float z)
{
	m_modelMat = glm::rotate(m_modelMat, radians, glm::vec3(x, y, z));
}

void Shape::draw()
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