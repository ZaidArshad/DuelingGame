#pragma once
#include "glm/glm.hpp"
#include "Model/VertexArray.h"
#include "Model/Texture.h"

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
	void rotateModel(float radians, float x, float y, float z);
	void draw();

	// -- Virtual -- //
	virtual std::vector<float> getPosition() = 0;
protected:
	int m_vertCount;
	VertexArray m_va;
	Texture* m_pTexture;
	glm::mat4 m_modelMat;
};