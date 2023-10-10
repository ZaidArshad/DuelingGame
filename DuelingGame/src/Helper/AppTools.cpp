#include "AppTools.h"
#include "Logger.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/gtc/matrix_transform.hpp"

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

float AppTools::calculateHeading(float x, float y)
{
	double heading = 0;
	if (x != 0 && y != 0)
	{
		heading = glm::atan(x/y);
	}
	else if (x != 0 || y < 0)
	{
		heading = glm::half_pi<double>();
	}

	if (y < 0)
	{
		heading += (heading > 0) ? glm::half_pi<double>() : -glm::half_pi<double>();
	}
	else
	{
		heading *= -1;
	}

	return heading;
}
