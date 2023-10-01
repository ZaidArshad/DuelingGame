#include "Camera.h"

Camera::Camera()
{
	m_view = glm::mat4(1.0f);
}

Camera::~Camera()
{
}

void Camera::setView(glm::mat4 view)
{
	m_view = view;
}

const glm::mat4 Camera::getView()
{
	return m_view;
}

void Camera::translate(float x, float y, float z)
{
	glm::translate(m_view, glm::vec3(x, y, z));
}