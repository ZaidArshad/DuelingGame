#include "Renderer.h"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
}
