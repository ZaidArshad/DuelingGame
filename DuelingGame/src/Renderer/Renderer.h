#pragma once

#include <vector>

#include "Model/Shape.h"

class Renderer
{
public:
	Renderer();
	~Renderer();
	void drawShapes();
	void addShape(const Shape& shape);
	void clear();
private:
	std::vector<Shape> m_shapes;
};

