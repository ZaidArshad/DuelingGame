#include "Player.h"

Player::Player()
{
	m_controller = InputController(0.01f);
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
	float x = 0;
	float y = 0;
	m_controller.move2D(window, &x, &y);
	m_cube.translate(-x, 0, y);
	//m_cube.rotate(-x, 0, 1, 0);
}
