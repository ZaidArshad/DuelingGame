#include "Player.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/vector_angle.hpp"
#include <iostream>

Player::Player()
{
	m_velocity = 0.01f;
	m_cube = Cube(0.05f);
	m_cube.translate(0.0f, 0.051f, -1.0f);
	m_cube.setTexture("res/Images/fella.png");
}

Player::~Player()
{
}

Shape* Player::getModel()
{
	return &m_cube;
}

void Player::move(GLFWwindow* window)
{
	int x = 0;
	int y = 0;

	m_controller.move2D(window, &x, &y);
	if (x == 0 && y == 0)
	{
		return;
	}

	double heading = 0;
	if (x != 0 && y != 0)
	{
		heading = glm::atan(x/y);
	}
	else if (x != 0)
	{
		heading = glm::half_pi<double>();
	}
	else if (y < 0)
	{
		heading = glm::half_pi<double>();
	}

	if (y < 0)
	{
		heading += (heading > 0) ? glm::half_pi<double>() : -glm::half_pi<double>();
	}
	else
	{
		heading *= -1;
	}

	std::cout << x << " " << y << " " << glm::degrees(heading) << std::endl;

	if (rotation != heading)
	{
		m_cube.rotate(-rotation, 0, 1, 0);
		m_cube.rotate(heading, 0, 1, 0);
		rotation = heading;
	}

	m_cube.rotate(-rotation, 0, 1, 0);
	m_cube.translate(-x*m_velocity, 0, y*m_velocity);
	m_cube.rotate(rotation, 0, 1, 0);
}
