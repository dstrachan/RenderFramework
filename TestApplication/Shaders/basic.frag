#version 150

uniform vec3 triangle_colour;

out vec4 colour;

void main()
{
	colour = vec4(triangle_colour, 1.0);
}