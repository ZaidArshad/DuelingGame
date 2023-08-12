#pragma once
#include "Logger.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <sstream>
#include <map>

std::map<GLenum, std::string> GLErrorSources =
{
	{GL_DEBUG_SOURCE_API,				"GL_DEBUG_SOURCE_API"},
	{GL_DEBUG_SOURCE_WINDOW_SYSTEM,		"GL_DEBUG_SOURCE_WINDOW_SYSTEM"},
	{GL_DEBUG_SOURCE_SHADER_COMPILER,	"GL_DEBUG_SOURCE_SHADER_COMPILER"},
	{GL_DEBUG_SOURCE_THIRD_PARTY,		"GL_DEBUG_SOURCE_THIRD_PARTY"},
	{GL_DEBUG_SOURCE_APPLICATION,		"GL_DEBUG_SOURCE_APPLICATION"},
	{GL_DEBUG_SOURCE_OTHER,				"GL_DEBUG_SOURCE_OTHER"}
};

std::map<GLenum, std::string> GLErrorTypes =
{
	{GL_DEBUG_TYPE_ERROR,				"GL_DEBUG_TYPE_ERROR"},
	{GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR,	"GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR"},
	{GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR,	"GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR"},
	{GL_DEBUG_TYPE_PORTABILITY,			"GL_DEBUG_TYPE_PORTABILITY"},
	{GL_DEBUG_TYPE_PERFORMANCE,			"GL_DEBUG_TYPE_PERFORMANCE"},
	{GL_DEBUG_TYPE_MARKER,				"GL_DEBUG_TYPE_MARKER"},
	{GL_DEBUG_TYPE_PUSH_GROUP,			"GL_DEBUG_TYPE_PUSH_GROUP"},
	{GL_DEBUG_TYPE_POP_GROUP,			"GL_DEBUG_TYPE_POP_GROUP"},
	{GL_DEBUG_TYPE_OTHER,				"GL_DEBUG_TYPE_OTHER"}
};

std::map<GLenum, std::string> GLErrorSeverity =
{
	{GL_DEBUG_SEVERITY_NOTIFICATION,	"GL_DEBUG_SEVERITY_NOTIFICATION"},
	{GL_DEBUG_SEVERITY_LOW,				"GL_DEBUG_SEVERITY_LOW"},
	{GL_DEBUG_SEVERITY_MEDIUM,			"GL_DEBUG_SEVERITY_MEDIUM"},
	{GL_DEBUG_SEVERITY_HIGH,			"GL_DEBUG_SEVERITY_HIGH"}
};

void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
	if (severity == GL_DEBUG_SEVERITY_NOTIFICATION)
	{
		return;
	}
	
	std::stringstream log;
	log << "[OpenGL Error] ("
		<< "Severity: " << GLErrorSeverity[severity]
		<< " Source: " << GLErrorSources[source]
		<< " Type: " << GLErrorTypes[type]
		<< " ID: " << id
		<< " Message: " << message
		<< ")" << std::endl;
	Logger::log(log.str());
}