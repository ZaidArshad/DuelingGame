#include "Renderer.h"

Renderer::Renderer(Shader* shader)
{
	m_shader = shader;
}

Renderer::~Renderer()
{
}

void Renderer::drawShapes()
{
	m_shader->useShader();
	for (Shape* shape : m_shapes)
	{
		m_shader->setFragmentColor(shape->getColor());
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
