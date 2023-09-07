#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

class VertexArray
{
public:
	VertexArray(const std::vector<double>& vertices,
				unsigned int stride,
				const std::vector<unsigned int>& indices);
	~VertexArray();
	void addBuffer(const std::vector<double>& vertices, unsigned int stride);
	void setIndices(const std::vector<unsigned int>& indices);
	void updateBuffer(unsigned int i, const std::vector<double>& vBuffer);
	void draw();
private:
	GLuint m_VAO;
	GLuint m_IBO;
	std::vector<GLuint> m_VBOs; 

	unsigned int m_offset;
	std::vector<unsigned int> m_indices;
};

