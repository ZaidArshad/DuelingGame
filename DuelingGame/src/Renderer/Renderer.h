#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <vector>

#include "Model/Camera.h"
#include "Shader/Shader.h"
#include "Shape/Shape.h"
#include "Helper/Apptools.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	// -- Getters -- //
	Camera* getCamera();
	
	// -- Utility -- //
	void updateMVP(glm::mat4 model, 
				   glm::mat4 view,
				   glm::mat4 projection,
				   Shader* shader);
	void addShape(Shape* shape, bool is3D = false);
	void drawShapes(Shader* shader);
	void clear();
private:
	std::vector<Shape*> m_2DShapes;
	std::vector<Shape*> m_3DShapes;

	Camera m_camera;
};

