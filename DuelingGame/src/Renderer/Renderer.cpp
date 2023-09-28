#include "Renderer.h"
#include "glm/gtc/matrix_transform.hpp"
#include "Helper/Apptools.h"

Renderer::Renderer()
{
	m_view = glm::mat4(1.0f);
	m_projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -2.0f, 2.0f);
}

Renderer::~Renderer()
{
}

void Renderer::setView(glm::mat4 view)
{
	m_view = view;
}

void Renderer::setProjection(glm::mat4 projection)
{
	m_projection = projection;
}

void Renderer::addShape(Shape* shape, bool is3D)
{
	if (is3D)
	{
		m_3DShapes.push_back(shape);
	}
	else
	{
		m_2DShapes.push_back(shape);
	}
}

void Renderer::drawShapes(Shader* shader)
{
	// Switch to orthographic projection for 3D shapes
	m_projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -2.0f, 2.0f);
	for (Shape* shape : m_2DShapes)
	{
		updateMVP(shape->getModelMatrix(), shader);
		shape->draw();
	}

	// Switch to perspective projection for 3D shapes
	m_projection = glm::perspective(45.0f,
									(float)WINDOW_WIDTH / (float)WINDOW_HEIGHT,
									0.1f,
									1000.0f);
	for (Shape* shape : m_3DShapes)
	{
		updateMVP(shape->getModelMatrix(), shader);
		shape->draw();
	}
}

void Renderer::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::updateMVP(glm::mat4 model, Shader* shader)
{
	glm::mat4 mvp = m_projection * m_view * model;
	GLint location = glGetUniformLocation(shader->getProgram(), "u_MVP");
	glUniformMatrix4fv(location, 1, GL_FALSE, &mvp[0][0]);
}