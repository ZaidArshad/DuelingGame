#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Error/GLError.h"

#include <string>
#include <fstream>

// Couldn't figure out how to cleanly singleton this
// Refered to this for help https://stackoverflow.com/a/64202104

class Logger
{
public:
	static void log(std::string msg);
	static void log(GLError err);

private:
	Logger();

	std::ofstream outFile;
	GLError lastErr;

	// Singleton instance
	static Logger instance;
};
