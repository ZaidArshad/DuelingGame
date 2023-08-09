#include "AppTools.hpp"

double AppTools::normalizeX(double position)
{
	return (position - WINDOW_WIDTH/2) / (WINDOW_WIDTH/2);
}

double AppTools::normalizeY(double position)
{
	return (WINDOW_HEIGHT/2 - position) / (WINDOW_HEIGHT/2);
}