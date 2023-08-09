#include "InputController.hpp"
#include<iostream>

InputController::InputController(double v)
{
	velocity = v;
}

void InputController::move2D(GLFWwindow* window, double* x, double* y)
{
	double left = glfwGetKey(window, GLFW_KEY_LEFT);
	double right = glfwGetKey(window, GLFW_KEY_RIGHT);
	double up = glfwGetKey(window, GLFW_KEY_UP);
	double down = glfwGetKey(window, GLFW_KEY_DOWN);

	*x += (right - left) * velocity;
	*y += (down - up) * velocity;
}