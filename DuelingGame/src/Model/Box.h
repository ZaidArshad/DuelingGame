#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Shape.h"

class Box : public Shape
{
public:
	Box(double x, double y, double w, double h);
	void setPosition(double x, double y);
private:
	// Used to calculate dimensions
	double xPos;
	double yPos;
	double width;
	double height;
};

