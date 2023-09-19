#pragma once
#include <GLFW/glfw3.h>

class InputController
{
public:
	InputController(float v);
	void move2D(GLFWwindow* window, float* x, float* y);
	void mouseDrag2D(GLFWwindow* window, double* x, double* y);
private:
	float velocity;
	bool m_mouseClicked;
	double m_originMouseX;
	double m_originMouseY;
};

