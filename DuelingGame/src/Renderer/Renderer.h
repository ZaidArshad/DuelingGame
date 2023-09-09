#pragma once

#include <vector>

#include "Shader/Shader.h"
#include "Model/Shape.h"
#include "Helper/Apptools.h"

class Renderer
{
public:
	Renderer();
	~Renderer();
	void addShape(Shape* shape);
	void drawShapes();
	void clear();
private:
	std::vector<Shape*> m_shapes;
};

