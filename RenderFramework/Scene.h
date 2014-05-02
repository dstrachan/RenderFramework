#pragma once

#include "stdafx.h"

#include "Mesh.h"
#include "Light.h"

namespace RenderFramework
{
	struct Scene
	{
		// Vector containing all meshes
		std::vector<std::shared_ptr<Mesh>> meshes;
		// Vector containing all lights
		std::vector<std::shared_ptr<Light>> lights;

		Scene();
		~Scene();
	};
}