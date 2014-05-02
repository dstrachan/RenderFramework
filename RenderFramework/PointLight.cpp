#include "stdafx.h"

#include "Light.h"

namespace RenderFramework
{
	PointLight::PointLight()
		: Light(), diffuse(glm::vec4(0.7f, 0.7f, 0.7f, 1.0f)),
		attenuation(glm::vec3(1.0f, 2.0f / 10.0f, 1.0f / (10.0f * 10.0f)))
	{
	}

	PointLight::~PointLight()
	{
	}
}