#include "Renderer.h"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
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
