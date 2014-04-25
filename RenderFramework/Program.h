#pragma once

#include "stdafx.h"

#include "Shader.h"

namespace RenderFramework
{
	class Program
	{
	public:
		GLuint id;
		std::vector<std::shared_ptr<Shader>> shaders;
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