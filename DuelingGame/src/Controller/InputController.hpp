#pragma once
#include <GLFW/glfw3.h>

class InputController
{
private:
	double velocity;
public:
	InputController(double v);
	void move2D(GLFWwindow* window, double* x, double* y);
};

