#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <vector>

#include "Shader/Shader.h"
#include "Model/Shape.h"
#include "Helper/Apptools.h"

class Renderer
{
public:
	Renderer();
	~Renderer();
	void setView(glm::mat4 view);
	void setProjection(glm::mat4 projection);
	void updateMVP(glm::mat4 model, Shader* shader);
	void addShape(Shape* shape);
	void drawShapes(Shader* shader);
	void clear();
private:
	std::vector<Shape*> m_shapes;
	glm::mat4 m_view;
	glm::mat4 m_projection;
};

