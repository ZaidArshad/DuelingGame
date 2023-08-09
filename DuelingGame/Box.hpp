#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Box
{
public:
	Box(double x, double y, double w, double h);
	void drawBox();
	void setPosition(double x, double y);
private:
	void generateBuffer();

	double xPos;
	double yPos;
	double width;
	double height;
	GLuint VAO;
	GLuint buffer;
};

