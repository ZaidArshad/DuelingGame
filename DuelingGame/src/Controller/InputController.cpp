#include "InputController.h"
#include "Helper/Apptools.h"
#include<iostream>

InputController::InputController()
{
	velocity = 0;
	m_originMouseX = 0;
	m_originMouseY = 0;
	m_mouseClicked = false;
}

InputController::InputController(float v)
{
	velocity = v;
	m_originMouseX = 0;
	m_originMouseY = 0;
	m_mouseClicked = false;
}

void InputController::move2D(GLFWwindow* window, float* x, float* y)
{
	int left = glfwGetKey(window, GLFW_KEY_LEFT);
	int right = glfwGetKey(window, GLFW_KEY_RIGHT);
	int up = glfwGetKey(window, GLFW_KEY_UP);
	int down = glfwGetKey(window, GLFW_KEY_DOWN);

	*x = (right - left) * velocity;
	*y = (up - down) * velocity;
}

void InputController::mouseDrag2D(GLFWwindow* window, double* x, double* y)
{
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2))
	{
		double curX, curY;
		glfwGetCursorPos(window, &curX, &curY);

		if (m_mouseClicked)
		{
			*x = AppTools::normalizeX(curX) - m_originMouseX;
			*y = m_originMouseY - AppTools::normalizeX(curY);
		}
		m_mouseClicked = true;
		m_originMouseX = AppTools::normalizeX(curX);
		m_originMouseY = AppTools::normalizeX(curY);
	}
	else
	{
		m_mouseClicked = false;
	}

}
