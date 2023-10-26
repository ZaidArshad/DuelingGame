#pragma once
#include <string>
#include <fstream>
#include <vector>

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
	static float calculateHeading(float x, float y);

	
	static void printVector(const std::vector<float>& vec);
};


