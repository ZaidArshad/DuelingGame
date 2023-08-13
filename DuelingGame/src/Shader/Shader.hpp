#pragma once
#include "AppTools.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

class Shader
{
public:
	Shader();
	Status generateShader(std::string vPath, std::string fPath);
	void useShader();
	void deleteShader();
	void setFragmentColor(float r, float g, float b, float a);

private:
	Status compileShader(GLuint& shader, std::string& shaderSource, GLenum type);
	std::string parseShaderFile(std::string& path);

	GLuint program;
};

