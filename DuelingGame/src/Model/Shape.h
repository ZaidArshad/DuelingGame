#pragma once
#include "glm/glm.hpp"
#include "VertexArray.h"
#include "Texture.h"

class Shape
{
public:
	Shape()
	{
		m_pTexture = nullptr;
		m_modelMat = glm::mat4(1.0f);
	}

	glm::mat4 getModelMatrix() { return m_modelMat; }

	virtual void draw() = 0;
	virtual std::vector<float> getPosition() = 0;
protected:
	VertexArray m_va;
	Texture* m_pTexture;
	glm::mat4 m_modelMat;
};