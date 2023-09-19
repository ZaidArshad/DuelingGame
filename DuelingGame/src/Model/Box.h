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
	Box(float x, float y, float w, float h);
	~Box();
	void setPosition(float x, float y);
	void setColor(float r, float g, float b, float a);
	void setTexture(const std::string& path);
	
	// Overloaded virtual functions of Shape
	void draw();
	glm::mat4 getModelMatrix();
private:
	std::vector<float> getPosition();

	// Used to calculate dimensions
	float m_x;
	float m_y;
	float m_width;
	float m_height;

	glm::mat4 m_modelMat;

	VertexArray m_va;
	Texture* m_pTexture;
};

