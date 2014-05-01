#pragma once

#include "stdafx.h"

#include "Shader.h"
#include "Uniform.h"

namespace RenderFramework
{
	struct Program
	{
		// OpenGL Program ID
		GLuint id;
		// Vector of Shaders that make up the Program
		std::vector<std::shared_ptr<Shader>> shaders;
		// A map of Uniforms in the compiled Program
		std::unordered_map<std::string, Uniform> uniforms;

		Program();
		~Program();
	};
}