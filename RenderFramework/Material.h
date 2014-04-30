#pragma once

#include "stdafx.h"

#include "Program.h"

namespace RenderFramework
{
	class Material
	{
	private:
		glm::vec4 emissive;
		glm::vec4 ambient;
		glm::vec4 diffuse;
		glm::vec4 specular;
		float shininess;

		std::shared_ptr<Program> program;
	public:
		Material();
		~Material();

		std::shared_ptr<Program> getProgram() const;
		void setProgram(const std::shared_ptr<Program> value);
		glm::vec4 getEmissive() const;
		void setEmissive(const glm::vec4& value);
		glm::vec4 getAmbient() const;
		void setAmbient(const glm::vec4& value);
		glm::vec4 getDiffuse() const;
		void setDiffuse(const glm::vec4& value);
		glm::vec4 getSpecular() const;
		void setSpecular(const glm::vec4& value);
		float getShininess() const;
		void setShininess(const float& value);
	};
}