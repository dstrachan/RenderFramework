#pragma once

#include "stdafx.h"

#include "Transform.h"

namespace RenderFramework
{
	struct Light : public Transform
	{
	protected:
		Light();
		virtual ~Light();
	};

	struct PointLight : public Light
	{
		// Diffuse colour
		glm::vec4 diffuse;
		// Attenuation values of the Light: x = constant; y = linear; z = quadratic
		glm::vec3 attenuation;

		PointLight();
		~PointLight();
	};

	/*class DirectionalLight : public Light
	{
	public:
		PointLight();
		~PointLight();
	};

	class SpotLight : public Light
	{
	public:
		SpotLight();
		~SpotLight();
	};*/
}