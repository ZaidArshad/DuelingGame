#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

#include "Helper/AppTools.h"
#include "Color.h"

class Shader
{
public:
	Shader();
	Status generateShader(const std::string& vPath, const std::string& fPath);
	GLuint getProgram();
	void useShader();
	void deleteShader();
	void setFragmentColor(const Color& color);

private:
	Status compileShader(GLuint& shader, std::string& shaderSource, GLenum type);
	std::string parseShaderFile(const std::string& path);

	GLuint program;
};

