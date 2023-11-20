#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Helper/AppTools.h"
#include "Options.h"

class App
{
public:
	App();
	Status run();
private:
	Status setup();
	void fpsCounter();

	double m_prevTime;
	unsigned int m_frameCount;

	GLFWwindow* m_window;
	Options* m_options;
};
