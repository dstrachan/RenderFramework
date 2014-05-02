#pragma once

#include "stdafx.h"

#include "Transform.h"

namespace RenderFramework
{
	class Light
	{
	protected:
		Light();
		virtual ~Light();
	public:
		// Transform to define the position, orientation and scale of the Light
		std::shared_ptr<Transform> transform;
		// Diffuse colour
		glm::vec4 diffuse;
	};

	class DirectionalLight : public Light
	{
	public:
		DirectionalLight();
		~DirectionalLight();
	};

	/*class PointLight : public Light
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