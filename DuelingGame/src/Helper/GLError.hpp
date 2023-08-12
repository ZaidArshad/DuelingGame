#pragma once
#include "Logger.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <sstream>
#include <map>

void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
	std::stringstream log;
	log << "[OpenGL Error] ("
		<< "Source: " << source
		<< " Type: " << type
		<< " ID: " << id
		<< " Severity: " << severity
		<< " Message: " << message
		<< ")" << std::endl;
	Logger::log(log.str());
}