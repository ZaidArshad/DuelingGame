#pragma once
#include "3rd/glm/glm.hpp"
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
	const glm::mat4 getModelMatrix();
	const glm::vec3 getRotation();

	// -- Utility -- //
	void shift(float x, float y, float z);
	void translate(float x, float y, float z);
	void rotate(glm::vec3 rotation);
	void setRotation(glm::vec3 rotation);
	void scale(float x, float y, float z);
	void resetModel();

	// -- Virtual -- //
	virtual void draw();
protected:
	VertexArray* m_pVA;
	int m_vertCount;
	Texture* m_pTexture;
	glm::vec3 m_rotation;
	glm::mat4 m_modelMat;
};