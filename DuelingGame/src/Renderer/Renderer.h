#pragma once

#include <vector>

#include "Model/Shape.h"
#include "Shader/Shader.h"
#include "Helper/Apptools.h"

class Renderer
{
public:
	Renderer(Shader* shader);
	~Renderer();
	void drawShapes();
	void addShape(const Shape& shape);
	void clear();
private:
	std::vector<Shape> m_shapes;
	Shader* m_shader;
};

