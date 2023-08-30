#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "AppTools.hpp"

class App
{
public:
	App();
	Status run();
private:
	GLFWwindow* window;
};
