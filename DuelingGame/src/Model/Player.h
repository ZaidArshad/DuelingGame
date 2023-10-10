#pragma once
#include "Shape/Cube.h"
#include "Controller/InputController.h"

class Player
{
public:
	Player();
	~Player();

	Shape* getModel();

	void move(GLFWwindow* window);
	
private:
	InputController m_controller;
	Cube m_cube;
};

