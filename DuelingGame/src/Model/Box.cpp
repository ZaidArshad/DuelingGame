#include "Box.h"
#include "Helper/AppTools.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

Box::Box(double x, double y, double w, double h)
{
	width = w;
	height = h;
	setPosition(x, y);
	
	std::vector<unsigned int> indices
	{
		0, 1, 2,
		1, 2, 3
	};
	setIndices(indices);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_DOUBLE, GL_TRUE, sizeof(double) * 2, 0);
}

void Box::setPosition(double x, double y)
{
	xPos = x;
	yPos = y;
	double left = AppTools::normalizeX(xPos);
	double right = AppTools::normalizeX(xPos + width);
	double top = AppTools::normalizeY(yPos);
	double bottom = AppTools::normalizeY(yPos + height);
	std::vector<double> positions
	{
		left,  top, 
		right, top,
		left,  bottom, 
		right, bottom
	};

	setVertices(positions);
}