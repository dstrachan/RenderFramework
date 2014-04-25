#pragma once

#include "stdafx.h"

#include "Shader.h"
#include "Uniform.h"

namespace RenderFramework
{
	class Program
	{
	public:
		GLuint id;
		std::vector<std::shared_ptr<Shader>> shaders;
		std::unordered_map<std::string, Uniform> uniforms;
		Program() : id(0) { }
		~Program()
		{
			if (id)
			{
				for (auto& s : shaders)
					glDetachShader(id, s->id);
				glDeleteShader(id);
				id = 0;
			}
		}
	};
}