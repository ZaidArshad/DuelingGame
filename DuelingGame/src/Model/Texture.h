#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

class Texture
{
public:
	Texture(const std::string& path);
	~Texture();
	void bind(unsigned int slot);
	void unbind();

private:
	std::string m_filePath;
	GLuint m_renderID;
	unsigned char* m_imgBuffer;
	int m_width;
	int m_height;
	int m_BPP;
};

