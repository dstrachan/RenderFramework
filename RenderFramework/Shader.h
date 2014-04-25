#pragma once

#include "stdafx.h"

namespace RenderFramework
{
	class Shader
	{
	public:
		GLuint id;
		GLenum type;
		Shader() : id(0), type(GL_VERTEX_SHADER) { }
		~Shader()
		{
			if (id)
			{
				glDeleteShader(id);
				id = 0;
			}
		}
	};
}