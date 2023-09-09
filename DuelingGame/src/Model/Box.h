#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "VertexArray.h"

class Box
{
public:
	Box(float x, float y, float w, float h);
	~Box();
	void setPosition(float x, float y);
	void draw();
private:
	std::vector<float> getPosition();

	// Used to calculate dimensions
	float m_x;
	float m_y;
	float m_width;
	float m_height;

	VertexArray m_va;
};

