#pragma once

#include "stdafx.h"

#include "Program.h"

namespace RenderFramework
{
	struct Material
	{
		// Emissive colour
		glm::vec4 emissive;
		// Ambient colour
		glm::vec4 ambient;
		// Diffuse colour
		glm::vec4 diffuse;
		// Specular colour
		glm::vec4 specular;
		// Shininess factor
		float shininess;

		// Program attached to the Material
		std::shared_ptr<Program> program;

		Material();
		~Material();
	};
}