#pragma once

#include "stdafx.h"

#include "Geometry.h"
#include "Material.h"

namespace RenderFramework
{
	class Mesh
	{
	private:
		std::shared_ptr<Geometry> geometry;
		std::shared_ptr<Material> material;
	public:
		Mesh();
		~Mesh();

		std::shared_ptr<Geometry> getGeometry() const;
		void setGeometry(const std::shared_ptr<Geometry>& value);
		std::shared_ptr<Material> getMaterial() const;
		void setMaterial(const std::shared_ptr<Material>& value);
	};
}