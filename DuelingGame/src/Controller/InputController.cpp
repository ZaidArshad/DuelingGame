#include "InputController.h"
#include<iostream>

InputController::InputController(float v)
{
	velocity = v;
}

void InputController::move2D(GLFWwindow* window, float* x, float* y)
{
	int left = glfwGetKey(window, GLFW_KEY_LEFT);
	int right = glfwGetKey(window, GLFW_KEY_RIGHT);
	int up = glfwGetKey(window, GLFW_KEY_UP);
	int down = glfwGetKey(window, GLFW_KEY_DOWN);

	*x += (right - left) * velocity;
	*y += (down - up) * velocity;
}