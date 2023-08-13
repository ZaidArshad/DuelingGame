#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

struct GLError
{
	GLenum source;
	GLenum type;
	GLuint id;
	GLenum severity;
	GLsizei length;
	const GLchar* message;
};

void GLAPIENTRY MessageCallback(GLenum source,
								GLenum type,
								GLuint id,
								GLenum severity,
								GLsizei length,
								const GLchar* message,
								const void* userParam);