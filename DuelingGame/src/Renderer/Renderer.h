#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <vector>

#include "Model/Camera.h"
#include "Shader/Shader.h"
#include "Model/Shape.h"
#include "Helper/Apptools.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	// -- Setters -- //
	void setProjection(glm::mat4 projection);

	// -- Getters -- //
	Camera* getCamera();
	
	// -- Utility -- //
	void updateMVP(glm::mat4 model, Shader* shader);
	void addShape(Shape* shape, bool is3D = false);
	void drawShapes(Shader* shader);
	void clear();
private:
	std::vector<Shape*> m_2DShapes;
	std::vector<Shape*> m_3DShapes;

	Camera m_camera;
	glm::mat4 m_projection;
};

