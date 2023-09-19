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

void Renderer::drawShapes()
{
	for (Shape* shape : m_shapes)
	{
		shape->draw();
	}
}

void Renderer::clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
}
