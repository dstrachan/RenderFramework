#pragma once

#include "stdafx.h"

#include "Mesh.h"
#include "Light.h"

namespace RenderFramework
{
	struct Scene
	{
		// Vector containing all Meshes
		std::vector<std::shared_ptr<Mesh>> meshes;
		// Vector containing all PointLights
		std::vector<std::shared_ptr<PointLight>> pointLights;

		Scene();
		~Scene();
	};
}