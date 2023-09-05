#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "Shader/Color.h"

// Base class for model objects
class Shape
{
public:
	Shape();
	~Shape();
	void draw();
	void setVertices(const std::vector<double>& vertices);
	void setIndices(const std::vector<unsigned int>& indices);

	// Values must be normalized
	void setColor(float r, float g, float b, float a);
	Color getColor();
private:
	std::vector<double> m_vertices;
	std::vector<unsigned int> m_indices;

	Color m_color;

	// Buffers
	GLuint m_VAO;
	GLuint m_VBO;
	GLuint m_IBO;
};

