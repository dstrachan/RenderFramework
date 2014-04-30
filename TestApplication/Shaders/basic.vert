#version 330

layout (location = 0) in vec3 position;

uniform mat4 view, proj;

void main()
{
	gl_Position = proj * view * vec4(position, 1.0);
}