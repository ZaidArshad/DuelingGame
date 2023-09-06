#include "Renderer.h"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::drawShapes(Shader& shader)
{
	shader.useShader();
	for (Shape* shape : m_shapes)
	{
		shader.setFragmentColor(shape->getColor());
		shape->draw();
	}
}

void Renderer::addShape(Shape* shape)
{
	m_shapes.push_back(shape);
}

void Renderer::clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
}
