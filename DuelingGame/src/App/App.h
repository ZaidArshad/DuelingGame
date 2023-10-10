#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Helper/AppTools.h"
#include "Options.h"

class App
{
public:
	App();
	Status setup();
	Status run();
private:
	GLFWwindow* m_window;
	Options* m_options;
};
