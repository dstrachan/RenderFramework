#include "stdafx.h"

#include "Light.h"

namespace RenderFramework
{
	Light::Light()
		: diffuse(glm::vec4(0.7f, 0.7f, 0.7f, 1.0f))
	{
	}

	Light::~Light()
	{
	}
}