#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>

// Base class for model objects
class Shape
{
public:
	Shape();
	~Shape();
	void draw();
	void setVertices(const std::vector<double>& vertices);
	void setIndices(const std::vector<unsigned int>& indices);
private:
	std::vector<double> m_vertices;
	std::vector<unsigned int> m_indices;

	// Buffers
	GLuint m_VAO;
	GLuint m_VBO;
	GLuint m_IBO;
};

