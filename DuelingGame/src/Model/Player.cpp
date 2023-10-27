#include "Player.h"
#include "Helper/Apptools.h"
#include "glm/gtc/matrix_transform.hpp"
#include <iostream>

Player::Player()
{
	m_model = new Model("res/Models/waddle/waddle.obj");
	m_model->setTexture("res/Models/waddle/HrDee.00.png");
	m_model->scale(0.1f, 0.1f, 0.1f);
	m_model->translate(0.0f, 0.0f, 0.0f);
	m_velocity = 0.25;
}

Player::~Player()
{
	delete m_model;
}

Shape* Player::getModel()
{
	return m_model;
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

	float heading = AppTools::calculateHeading(x, z);
	if (m_model->getRotation()[1] != heading)
	{
		m_model->setRotation(glm::vec3(0, heading, 0));
		m_rotation = heading;
	}

	m_model->shift(-x*m_velocity, 0, z*m_velocity);
}
