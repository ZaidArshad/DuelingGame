#include "Shape.h"
#include "glm/gtc/matrix_transform.hpp"

Shape::Shape()
{
	m_pTexture = nullptr;
	m_modelMat = glm::mat4(1.0f);
}

glm::mat4 Shape::getModelMatrix()
{
	return m_modelMat;
}

void Shape::translate(float x, float y, float z)
{
	m_modelMat = glm::translate(m_modelMat, glm::vec3(x, y, z));
}

void Shape::rotateModelX(float radians)
{
	m_modelMat = glm::rotate(m_modelMat, radians, glm::vec3(0.0, 1.0, 0.0));
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