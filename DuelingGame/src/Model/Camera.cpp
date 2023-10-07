#include "Camera.h"
#include "Helper/Apptools.h"

Camera::Camera()
{
	m_view = glm::mat4(1.0f);
	m_orthoProjection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -2.0f, 2.0f);
	m_perspProjection = glm::perspective(45.0f,
		(float)WINDOW_WIDTH / (float)WINDOW_HEIGHT,
		0.1f,
		1000.0f);
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

const glm::mat4 Camera::getOrthoProjection()
{
	return m_orthoProjection;
}

const glm::mat4 Camera::getPerpsProjection()
{
	return m_perspProjection;
}

void Camera::translate(float x, float y, float z)
{
	m_view = glm::translate(m_view, glm::vec3(x, y, z));
}

void Camera::rotate(float radians, float x, float y, float z)
{
	m_view = glm::rotate(m_view, radians, glm::vec3(x, y, z));
}

void Camera::followModel(glm::mat4 model, float x, float y, float z)
{
	glm::vec3 modelPos = model[3];
	glm::vec3 cameraPos = glm::vec3(modelPos[0] + x, modelPos [1] - y, modelPos[2] +z);
	m_view = glm::lookAt(cameraPos,
						 modelPos,
						 glm::vec3(0, 1, 0));
	//m_view = glm::inverse(model);
	//m_view = glm::translate(m_view, glm::vec3(0, 0, -1));
}
