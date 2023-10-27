#pragma once
#include "Shape/Model.h"
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
	Model* m_model;

	float m_velocity;
	double m_rotation = 0;
};

