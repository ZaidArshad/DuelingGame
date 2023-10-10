#pragma once
#include "glm/glm.hpp"
#include "Renderer/VertexArray.h"
#include "Renderer/Texture.h"

class Shape
{
public:
	Shape();
	~Shape();

	// -- Setters -- //
	void setColor(float r, float g, float b, float a);
	void setTexture(const std::string& path);

	// -- Getters -- //
	glm::mat4 getModelMatrix();

	// -- Utility -- //
	void translate(float x, float y, float z);
	void rotate(float radians, float x, float y, float z);
	void scale(float x, float y, float z);
	void resetModel();
	void draw();

	// -- Virtual -- //
	virtual std::vector<float> getPosition() = 0;
protected:
	int m_vertCount;
	VertexArray m_va;
	Texture* m_pTexture;
	glm::mat4 m_modelMat;
};