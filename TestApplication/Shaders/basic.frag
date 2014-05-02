#version 410

layout (location = 0) in vec3 transformedPosition;
layout (location = 1) smooth in vec3 transformedNormal;

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

out vec4 colour;

void main()
{
	vec3 l = normalize(lightPos - transformedPosition);
	float s = max(0.0, dot(l, transformedNormal));
	colour = s * (materialDiffuse * lightDiffuse);
}