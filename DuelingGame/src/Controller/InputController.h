#pragma once
#include <GLFW/glfw3.h>

class InputController
{
public:
	InputController(float v);
	void move2D(GLFWwindow* window, float* x, float* y);
private:
	float velocity;
};

