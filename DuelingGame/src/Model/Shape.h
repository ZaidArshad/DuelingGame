#pragma once
#include "glm/glm.hpp"
#include "VertexArray.h"
#include "Texture.h"

class Shape
{
public:
	Shape();
	glm::mat4 getModelMatrix();
	void translate(float x, float y, float z);
	void rotateModelX(float radians);
	void draw();

	virtual std::vector<float> getPosition() = 0;
protected:
	VertexArray m_va;
	Texture* m_pTexture;
	glm::mat4 m_modelMat;
};