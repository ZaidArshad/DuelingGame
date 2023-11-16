#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "Texture.h"

struct VertexLayout
{
	GLuint VBO = 0;
	std::vector<float> vertices;
	unsigned int stride = 0;
};

class VertexArray
{
public:
	VertexArray();
	VertexArray(const std::vector<float>& vertices,
				unsigned int stride,
				const std::vector<unsigned int>& indices);
	~VertexArray();

	void bind();
	void unbind();
	void addBuffer(const std::vector<float>& vertices, unsigned int stride);
	void setIndices(const std::vector<unsigned int>& indices);
	void updateBuffer(unsigned int i, const std::vector<float>& vertices, GLenum drawType);
	void draw();
private:
	GLuint m_VAO;
	GLuint m_IBO;
	std::vector<VertexLayout> m_vertexLayouts;
	std::vector<unsigned int> m_indices;
};

