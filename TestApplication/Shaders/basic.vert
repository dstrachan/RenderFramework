#version 330

layout (location = 0) in vec3 position;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;
uniform mat3 N;

void main()
{
	mat4 MVP = P * V * M;
	gl_Position = MVP * vec4(position, 1.0);
}