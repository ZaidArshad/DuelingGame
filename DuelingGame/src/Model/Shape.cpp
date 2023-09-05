#include "Shape.h"
#include <algorithm>
#include <iostream>

Shape::Shape()
{
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_IBO);

	m_color = Color{0.0f, 1.0f, 1.0f, 1.0f};
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

void Shape::setColor(float r, float g, float b, float a)
{
	m_color.r = r;
	m_color.g = g;
	m_color.b = b;
	m_color.a = a;
	std::cout << m_color.r << " " << r << std::endl;
}

Color Shape::getColor()
{
	return m_color;
}

void Shape::draw()
{
	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(m_VAO);
}
