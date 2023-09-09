#version 400 core

in vec4 out_color;

out vec4 color;

void main()
{
	if (out_color.x != 0.0f ||
		out_color.y != 0.0f || 
		out_color.z != 0.0f)
	{
		color = out_color;
	}
	else
	{
		color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	}
};