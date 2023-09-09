#pragma once
#include <string>
#include <fstream>

#define Status unsigned int

static const int WINDOW_WIDTH = 640;
static const int WINDOW_HEIGHT = 480;

static const Status STATUS_OK = 0U;
static const Status STATUS_BAD = 1U;

class AppTools
{
public:
	static float normalizeX(float position);
	static float normalizeY(float position);
};


