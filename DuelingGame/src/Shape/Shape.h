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
	void draw();

	// -- Virtual -- //
	virtual std::vector<float> getPosition() = 0;
protected:
	int m_vertCount;
	glm::vec3 m_rotation;
	VertexArray m_va;
	Texture* m_pTexture;
	glm::mat4 m_modelMat;
};