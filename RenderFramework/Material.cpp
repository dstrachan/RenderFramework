#include "stdafx.h"

#include "Material.h"

namespace RenderFramework
{
	Material::Material()
		: emissive(glm::vec4(0.7f, 0.7f, 0.7f, 1.0f)),
		ambient(glm::vec4(0.7f, 0.7f, 0.7f, 1.0f)),
		diffuse(glm::vec4(0.7f, 0.7f, 0.7f, 1.0f)),
		specular(glm::vec4(0.7f, 0.7f, 0.7f, 1.0f)),
		shininess(10.0f)
	{
	}

	Material::~Material()
	{
	}
}