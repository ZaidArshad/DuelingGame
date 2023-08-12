#include "AppTools.hpp"
#include "Logger.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <sstream>

double AppTools::normalizeX(double position)
{
	return (position - WINDOW_WIDTH/2) / (WINDOW_WIDTH/2);
}

double AppTools::normalizeY(double position)
{
	return (WINDOW_HEIGHT/2 - position) / (WINDOW_HEIGHT/2);
}

void AppTools::clearOpenGLErrors()
{
	while (glGetError() != GL_NO_ERROR);
}

void AppTools::checkOpenGLError()
{
	while (GLenum err = glGetError())
	{
		std::stringstream log;
		log << "[OpenGL Error]" << err << std::endl;
		Logger::log(log.str());
	}
}