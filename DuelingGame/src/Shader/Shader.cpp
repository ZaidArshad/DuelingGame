#include "Shader.hpp"
#include "Logger.hpp"

#include<fstream>
#include<sstream>
#include<iostream>

Shader::Shader()
{
    program = glCreateProgram();
}

Status Shader::generateShader(std::string vPath, std::string fPath)
{
    std::string vShaderSource = parseShaderFile(vPath);
    std::string fShaderSource = parseShaderFile(fPath);

    // TODO: handle status
    GLuint vShader, fShader;
    compileShader(vShader, vShaderSource, GL_VERTEX_SHADER);
    compileShader(fShader, fShaderSource, GL_FRAGMENT_SHADER);
    glAttachShader(program, vShader);
    glAttachShader(program, fShader);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vShader);
    glDeleteShader(fShader);
    return Status::OK;
}

Status Shader::compileShader(GLuint& shader, std::string& shaderSource, GLenum type)
{
    shader = glCreateShader(type);
    const char* src = shaderSource.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    GLint result;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*) _malloca(length * sizeof(char));
        glGetShaderInfoLog(shader, length, &length, message);
        std::stringstream log;
        log << "Failed to compile " 
                  << (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
                  << " shader.\n"
                  << message << std::endl;
        Logger::log(log.str());
        glDeleteShader(shader);
        return Status::BAD;
    }

    return Status::OK;
}

void Shader::useShader()
{
	glUseProgram(program);
}

void Shader::deleteShader()
{
	glDeleteProgram(program);
}

std::string Shader::parseShaderFile(std::string& path)
{
	std::ifstream stream(path);
	std::stringstream buffer;
	buffer << stream.rdbuf();
	return buffer.str();
}