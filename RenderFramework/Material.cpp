#include "stdafx.h"

#include "Material.h"

namespace RenderFramework
{
	Material::Material()
		: emissive(glm::vec4(0.7f, 0.7f, 0.7f, 1.0f)),
		ambient(glm::vec4(0.7f, 0.7f, 0.7f, 1.0f)),
		diffuse(glm::vec4(0.7f, 0.7f, 0.7f, 1.0f)),
		specular(glm::vec4(0.7f, 0.7f, 0.7f, 1.0f)),
		shininess(10.0f)
	{
	}

	Material::~Material()
	{
	}

	std::shared_ptr<Program> Material::getProgram() const
	{
		return program;
	}

	void Material::setProgram(const std::shared_ptr<Program> value)
	{
		program = value;
	}

	glm::vec4 Material::getEmissive() const
	{
		return emissive;
	}

	void Material::setEmissive(const glm::vec4& value)
	{
		emissive = value;
	}

	glm::vec4 Material::getAmbient() const
	{
		return ambient;
	}

	void Material::setAmbient(const glm::vec4& value)
	{
		ambient = value;
	}

	glm::vec4 Material::getDiffuse() const
	{
		return diffuse;
	}

	void Material::setDiffuse(const glm::vec4& value)
	{
		diffuse = value;
	}

	glm::vec4 Material::getSpecular() const
	{
		return specular;
	}

	void Material::setSpecular(const glm::vec4& value)
	{
		specular = value;
	}

	float Material::getShininess() const
	{
		return shininess;
	}

	void Material::setShininess(const float& value)
	{
		shininess = value;
	}
}