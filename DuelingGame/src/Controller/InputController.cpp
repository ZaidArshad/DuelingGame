#include "InputController.h"
#include "Helper/Apptools.h"
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

void InputController::mouseMove2D(GLFWwindow* window, double* x, double* y)
{
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2))
	{
		double curX, curY;
		glfwGetCursorPos(window, &curX, &curY);
		if (!m_mouseClicked)
		{
			m_originMouseX = *x - curX;
			m_originMouseY = *y - curY;
		}
		m_mouseClicked = true;

		*x = m_originMouseX + curX;
		*y = m_originMouseY + curY;
	}
	else
	{
		m_mouseClicked = false;
	}
}
