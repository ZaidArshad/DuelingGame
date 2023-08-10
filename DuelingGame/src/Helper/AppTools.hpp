#pragma once
static const int WINDOW_WIDTH = 640;
static const int WINDOW_HEIGHT = 480;

static enum class Status : unsigned int
{
	OK = 0,
	BAD = 1
};

class AppTools
{
public:
	static double normalizeX(double position);
	static double normalizeY(double position);
};

