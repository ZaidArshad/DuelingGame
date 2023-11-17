#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "3rd/glm/glm.hpp"
#include "Shape.h"

class Box : public Shape
{
public:
	Box(float w, float h);
	~Box();
	void makeTiled(float rows, float cols);
	
	// -- Utility -- //
	std::vector<float> getPosition();

private:
	float m_width;
	float m_height;
};

