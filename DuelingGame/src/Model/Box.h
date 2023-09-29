#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "Shape.h"
#include "Texture.h"
#include "Shader/Shader.h"
#include "VertexArray.h"

class Box : public Shape
{
public:
	Box(float w, float h);
	~Box();
	
	// -- Overload -- //
	std::vector<float> getPosition() override;

private:
	float m_width;
	float m_height;
};

