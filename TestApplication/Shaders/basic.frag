#version 330

layout (location = 0) in vec4 in_colour;

out vec4 colour;

void main()
{
	colour = in_colour;
}