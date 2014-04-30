#version 330

layout (location = 0) in vec3 position;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;
uniform mat3 N;

uniform vec4 emissive;
uniform vec4 ambient;
uniform vec4 diffuse;
uniform vec4 specular;
uniform float shininess;

layout (location = 0) out vec4 colour;

void main()
{
	mat4 MVP = P * V * M;
	gl_Position = MVP * vec4(position, 1.0);
	colour = diffuse;
}