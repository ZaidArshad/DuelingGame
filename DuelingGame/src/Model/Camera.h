#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Camera
{
public:
	Camera();
	~Camera();

	// -- Setters -- //
	void setView(glm::mat4 view);

	// -- Getters -- //
	const glm::mat4 getView();
	const glm::mat4 getOrthoProjection();
	const glm::mat4 getPerpsProjection();

	// -- Utility -- //
	void translate(float x, float y, float z);
	void rotate(float radians, float x, float y, float z);

private:
	glm::mat4 m_view;
	glm::mat4 m_orthoProjection;
	glm::mat4 m_perspProjection;
};

