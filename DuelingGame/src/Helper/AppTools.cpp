#include "AppTools.h"
#include "Logger.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "3rd/glm/gtc/matrix_transform.hpp"
#include "3rd/glm/gtx/vector_angle.hpp"

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

// Calculated for 45 degree special triangle
float AppTools::calculateHeading(float x, float y)
{
	double heading = 0;
	x = -x;
	if (x != 0 && y != 0)
	{
		heading = glm::atan(x/y);
	}
	// When y is zero
	else if (x != 0)
	{
		heading = x * glm::half_pi<double>();
	}
	if (y < 0)
	{
		heading += glm::pi<double>();
	}

	return heading;
}

void AppTools::printVector(const std::vector<float>& vec)
{
	for (float f : vec)
	{
		std::cout << f << " ";
	}
	std::cout << std::endl;
}
