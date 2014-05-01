#pragma once

#include "stdafx.h"

#include "Mesh.h"

namespace RenderFramework
{
	struct Scene
	{
		// Vector containing all meshes
		std::vector<std::shared_ptr<Mesh>> meshes;

		Scene();
		~Scene();
	};
}