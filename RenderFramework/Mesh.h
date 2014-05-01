#pragma once

#include "stdafx.h"

#include "Geometry.h"
#include "Material.h"
#include "Transform.h"

namespace RenderFramework
{
	struct Mesh
	{
		// Geometry to define the shape of the Mesh
		std::shared_ptr<Geometry> geometry;
		// Material to define the appearance of the Mesh
		std::shared_ptr<Material> material;
		// Transform to define the position, orientation and scale of the Mesh
		std::shared_ptr<Transform> transform;

		Mesh();
		~Mesh();
	};
}