#include "Shape.h"
#include <algorithm>

Shape::Shape()
{
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_IBO);
}

Shape::~Shape()
{
}

void Shape::setVertices(const std::vector<double>& vertices)
{
	m_vertices = vertices;
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(double), m_vertices.data(), GL_STATIC_DRAW);
}

void Shape::setIndices(const std::vector<unsigned int>& indices)
{
	m_indices = indices;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), m_indices.data(), GL_STATIC_DRAW);
}

void Shape::draw()
{
	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(m_VAO);
}
