#include "Shape.h"
#include "Shader/Color.h"
#include "3rd/glm/gtc/matrix_transform.hpp"

Shape::Shape()
{
	m_pVA = new VertexArray();
	m_vertCount = 0;
	m_pTexture = nullptr;
	m_rotation = glm::vec3(0.0f);
	m_modelMat = glm::mat4(1.0f);
}

Shape::~Shape()
{
	delete m_pVA;
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
	m_pVA->updateBuffer(1, colors, GL_STATIC_DRAW);
}

void Shape::setTexture(const std::string& path)
{
	std::vector<float> colors;
	for (int i = 0; i < m_vertCount; i++)
	{
		colors.insert(colors.end(), COLOR_TEXTURE.begin(), COLOR_TEXTURE.end());
	}
	m_pVA->updateBuffer(1, colors, GL_STATIC_DRAW);
	m_pTexture = new Texture(path);
}

// -- Getters -- //
const glm::mat4 Shape::getModelMatrix()
{
	return m_modelMat;
}

const glm::vec3 Shape::getRotation()
{
	return m_rotation;
}

void Shape::shift(float x, float y, float z)
{
	glm::vec3 rotation = m_rotation;
	setRotation(glm::vec3(0.0f));
	translate(x, y, z);
	setRotation(rotation);
}

//  -- Utility -- //
void Shape::translate(float x, float y, float z)
{
	m_modelMat = glm::translate(m_modelMat, glm::vec3(x, y, z));
}

void Shape::rotate(glm::vec3 rotation)
{
	for (int i = 0; i < 3; i++)
	{
		glm::vec3 axis = glm::mat4(1.0f)[i];
		m_modelMat = glm::rotate(m_modelMat, rotation[i], axis);
	}
	m_rotation += rotation;
}

void Shape::setRotation(glm::vec3 rotation)
{
	rotate(-m_rotation);
	rotate(rotation);
}

void Shape::scale(float x, float y, float z)
{
	m_modelMat = glm::scale(m_modelMat, glm::vec3(x, y, z));
}

void Shape::resetModel()
{
	m_modelMat = glm::mat4(1.0f);
}

void Shape::draw()
{
	if (m_pTexture)
	{
		m_pTexture->bind(0);
		m_pVA->draw();
		m_pTexture->unbind();
	}
	else
	{
		m_pVA->draw();
	}
}