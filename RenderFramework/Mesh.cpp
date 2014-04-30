#include "stdafx.h"

#include "Mesh.h"

namespace RenderFramework
{
	Mesh::Mesh()
	{
	}

	Mesh::~Mesh()
	{
	}

	std::shared_ptr<Geometry> Mesh::getGeometry() const
	{
		return geometry;
	}

	void Mesh::setGeometry(const std::shared_ptr<Geometry>& value)
	{
		geometry = value;
	}

	std::shared_ptr<Material> Mesh::getMaterial() const
	{
		return material;
	}

	void Mesh::setMaterial(const std::shared_ptr<Material>& value)
	{
		material = value;
	}
}