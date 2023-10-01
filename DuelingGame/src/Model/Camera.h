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

	// -- Utility -- //
	void translate(float x, float y, float z);

private:
	glm::mat4 m_view;
};

