#include "VertexArray.h"

VertexArray::VertexArray(const std::vector<double>& vertices,
						 unsigned int stride,
						 const std::vector<unsigned int>& indices)
{
	m_VAO = 0;
	m_IBO = 0;
	m_offset = 0;

	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);
	addBuffer(vertices, stride);

	glGenBuffers(1, &m_IBO);
	setIndices(indices);
}

VertexArray::~VertexArray()
{
}

void VertexArray::addBuffer(const std::vector<double>& vertices, unsigned int stride)
{
	glBindVertexArray(m_VAO);

	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(double),
				 vertices.data(), GL_STATIC_DRAW);

	int index = m_VBOs.size();
	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, 4, GL_DOUBLE, GL_TRUE,
						  sizeof(double) * stride,
						  (const void*)m_offset);
	m_offset += sizeof(double) * stride;
	m_VBOs.push_back(VBO);
}

void VertexArray::setIndices(const std::vector<unsigned int>& indices)
{
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			  	 indices.size() * sizeof(unsigned int),
				 indices.data(), GL_STATIC_DRAW);
	m_indices = indices;
}

void VertexArray::updateBuffer(unsigned int i, const std::vector<double>& vBuffer)
{
}

void VertexArray::draw()
{
	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(m_VAO);
}
