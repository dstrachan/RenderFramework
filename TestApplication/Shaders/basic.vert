#version 410

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;
uniform mat3 N;

uniform vec4 emissive;
uniform vec4 ambient;
uniform vec4 materialDiffuse;
uniform vec4 specular;
uniform float shininess;

uniform vec3 lightPos;
uniform vec4 lightDiffuse;

layout (location = 0) out vec4 colour;

void main()
{
	mat4 MV = V * M;
	mat4 MVP = P * MV;
	gl_Position = MVP * vec4(position, 1.0);

	vec3 l = (MV * vec4(lightPos, 1.0)).xyz - (MV * vec4(position, 1.0)).xyz;
	vec3 n = normalize(N * normal);
	vec4 Kd = materialDiffuse * lightDiffuse;
	colour = Kd * max(0.0, dot(n, l));
}