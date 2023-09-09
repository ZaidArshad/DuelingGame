#include "AppTools.h"
#include "Logger.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <sstream>

float AppTools::normalizeX(float position)
{
	return (position - WINDOW_WIDTH/2) / (WINDOW_WIDTH/2);
}

float AppTools::normalizeY(float position)
{
	return (WINDOW_HEIGHT/2 - position) / (WINDOW_HEIGHT/2);
}