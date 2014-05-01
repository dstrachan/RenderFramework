#pragma once

#include "stdafx.h"

#include "Mesh.h"

namespace RenderFramework
{
	class Scene
	{
	public:
		// Vector containing all meshes
		std::vector<std::shared_ptr<Mesh>> meshes;

		Scene();
		~Scene();
	};
}