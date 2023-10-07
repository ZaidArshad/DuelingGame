#include "VertexArray.h"
#include "Helper/Logger.h"

VertexArray::VertexArray()
{
	m_VAO = 0;
	m_IBO = 0;
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);
	glGenBuffers(1, &m_IBO);
}

VertexArray::VertexArray(const std::vector<float>& vertices,
						 unsigned int stride,
						 const std::vector<unsigned int>& indices)
{
	m_VAO = 0;
	m_IBO = 0;
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);
	addBuffer(vertices, stride);

	glGenBuffers(1, &m_IBO);
	setIndices(indices);
}

VertexArray::~VertexArray()
{
}

void VertexArray::bind()
{
	glBindVertexArray(m_VAO);
}

void VertexArray::unbind()
{
	glBindVertexArray(0);
}

void VertexArray::addBuffer(const std::vector<float>& vertices, 
							unsigned int stride)
{
	glBindVertexArray(m_VAO);

	// Layout generation
	VertexLayout layout;
	layout.vertices = vertices;
	layout.stride = stride;

	// VBO generation
	glGenBuffers(1, &layout.VBO);
	glBindBuffer(GL_ARRAY_BUFFER, layout.VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float),
				 vertices.data(), GL_STATIC_DRAW);

	// Binding VBO to VAO
	int index = m_vertexLayouts.size();
	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, layout.stride, GL_FLOAT, GL_FALSE,
						  0,
						  NULL);
	m_vertexLayouts.push_back(layout);
}

void VertexArray::setIndices(const std::vector<unsigned int>& indices)
{
	glBindVertexArray(m_VAO);

	// IBO Generation
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			  	 indices.size() * sizeof(unsigned int),
				 indices.data(), GL_STATIC_DRAW);
	m_indices = indices;
}

void VertexArray::updateBuffer(unsigned int i, const std::vector<float>& vertices)
{
	if (i > m_vertexLayouts.size())
	{
		Logger::log("Index " + std::to_string(i) +
					" out of bounds. Number of vertice layouts = " +
					std::to_string(m_vertexLayouts.size()));
		return;
	}

	glBindVertexArray(m_VAO);

	// Updating layout
	VertexLayout* layout = &m_vertexLayouts[i];
	if (vertices.size() != layout->vertices.size())
	{
		Logger::log("Vertice size mismatch (" + 
					std::to_string(vertices.size()) + "," +
					std::to_string(layout->vertices.size()) + 
					") for vertices at index: " + std::to_string(i));
		return;
	}
	layout->vertices = vertices;

	// Updating VBO
	glBindBuffer(GL_ARRAY_BUFFER, layout->VBO);
	glBufferData(GL_ARRAY_BUFFER, layout->vertices.size() * sizeof(float),
		layout->vertices.data(), GL_STATIC_DRAW);

	// Binding VBO to VAO
	glEnableVertexAttribArray(i);
	glVertexAttribPointer(i, layout->stride, GL_FLOAT, GL_FALSE, 0, NULL);
}

void VertexArray::draw()
{
	glBindVertexArray(m_VAO);
	glDrawElements(GL_LINE_STRIP, m_indices.size(), GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);
}
