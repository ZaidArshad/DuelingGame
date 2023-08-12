#include "Box.hpp"
#include "AppTools.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

Box::Box(double x, double y, double w, double h)
{
	xPos = x;
	yPos = y;
	width = w;
	height = h;
	generateBuffers();
}

void Box::drawBox()
{
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void Box::setPosition(double x, double y)
{
	xPos = x;
	yPos = y;
	double left = AppTools::normalizeX(xPos);
	double right = AppTools::normalizeX(xPos + width);
	double top = AppTools::normalizeY(yPos);
	double bottom = AppTools::normalizeY(yPos + height);
	double positions[8] =
	{
		left,  top,
		right, top,
		left,  bottom,
		right, bottom
	};

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(double), positions, GL_DYNAMIC_DRAW);
}

void Box::generateBuffers()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// Create the buffer and set the vertex data
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &IBO);

	// Setting the index buffer for these vertices [(0,0),(0,1),(1,0),(1,1)]
	unsigned int indices[6] =
	{
		0, 1, 2,
		1, 2, 3
	};
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_DYNAMIC_DRAW);

	// Binds the buffer in setPosition
	setPosition(xPos, yPos);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_DOUBLE, GL_FALSE, sizeof(double) * 2, 0);
}