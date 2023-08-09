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
	generateBuffer();
}

void Box::drawBox()
{
	glBindVertexArray(VAO);
	glDrawArrays(GL_LINE_LOOP, 0, 4);
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

	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(double), positions, GL_DYNAMIC_DRAW);
}

void Box::generateBuffer()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	setPosition(xPos, yPos);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_DOUBLE, GL_FALSE, sizeof(double) * 2, 0);
}