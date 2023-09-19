#include "Renderer.h"

Renderer::Renderer()
{
	m_view = glm::mat4(1.0f);
	m_projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
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

void Renderer::addShape(Shape* shape)
{
	m_shapes.push_back(shape);
}

void Renderer::drawShapes(Shader* shader)
{
	for (Shape* shape : m_shapes)
	{
		updateMVP(shape->getModelMatrix(), shader);
		shape->draw();
	}
}

void Renderer::clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::updateMVP(glm::mat4 model, Shader* shader)
{
	glm::mat4 mvp = m_projection * m_view * model;
	GLint location = glGetUniformLocation(shader->getProgram(), "u_MVP");
	glUniformMatrix4fv(location, 1, GL_FALSE, &mvp[0][0]);
}