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
	int z = 0;

	m_controller.move2D(window, &x, &z);
	if (x == 0 && z == 0)
	{
		return;
	}

	double heading = 0;
	if (x != 0 && z != 0)
	{
		heading = glm::atan(x/z);
	}
	else if (x != 0 || z < 0)
	{
		heading = glm::half_pi<double>();
	}

	if (z < 0)
	{
		heading += (heading > 0) ? glm::half_pi<double>() : -glm::half_pi<double>();
	}
	else
	{
		heading *= -1;
	}

	if (m_cube.getRotation()[1] != heading)
	{
		m_cube.setRotation(glm::vec3(0, heading, 0));
		rotation = heading;
	}

	m_cube.shift(-x*m_velocity, 0, z*m_velocity);
}
