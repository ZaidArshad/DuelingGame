#version 400 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 texCoord;

out vec4 out_color;
out vec2 out_texCoord;

void main()
{
	gl_Position = vec4(position, 0, 1.0);
	out_color = color;
	out_texCoord = texCoord;
};