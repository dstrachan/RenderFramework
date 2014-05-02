#version 410

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;
uniform mat3 N;
uniform mat4 MV;
uniform mat4 MVP;

uniform vec4 emissive;
uniform vec4 ambient;
uniform vec4 materialDiffuse;
uniform vec4 specular;
uniform float shininess;

uniform vec3 lightPos;
uniform vec4 lightDiffuse;

layout (location = 0) out vec3 transformedPosition;
layout (location = 1) smooth out vec3 transformedNormal;

void main()
{
	gl_Position = MVP * vec4(position, 1.0);

	transformedPosition = (M * vec4(position, 1.0)).xyz;
	transformedNormal = normalize(N * normal);
}